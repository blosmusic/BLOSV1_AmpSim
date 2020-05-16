/*
  ==============================================================================
 BLOS V1 Guitar Amp Sim submitted as part of the Masters in Music program in DKIT
 
 References for code in this project
 How to Build an Awesome Distortion: https://www.youtube.com/watch?v=iNCR5flSuDs
 Building a Filter Plugin Using the DSP Module IIR Filter: https://www.youtube.com/watch?v=YJ4YbV6TDo0
 The difference between FIR & IIR filters:
 http://www.iowahills.com/A8FirIirDifferences.html
 https://www.minidsp.com/applications/dsp-basics/fir-vs-iir-filtering

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <cmath>
//==============================================================================
MajorProjectAudioProcessor::MajorProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
,valueTree(*this, nullptr, "PARAMETERS",
AudioProcessorValueTreeState::ParameterLayout(
    std::make_unique<AudioParameterBool>("io", "IO", true),
    std::make_unique<AudioParameterFloat>("volume", "VOLUME", NormalisableRange<float>(0.0f, 11.0f), 1.0f),
    std::make_unique<AudioParameterFloat>("gain", "GAIN", NormalisableRange<float>(1.0f, 3000.0f), 1000.0f),
    std::make_unique<AudioParameterFloat>("presence", "PRESENCE", NormalisableRange<float>(0.1f, 1.0f), 0.4f),
    std::make_unique<AudioParameterFloat>("master", "MASTER", NormalisableRange<float>(0.0f, 11.0f), 5.0f),
    std::make_unique<AudioParameterFloat>("res", "RES", NormalisableRange<float>(0.1f, 10.0f), 1.0f),
    std::make_unique<AudioParameterFloat>("treb", "TREB", NormalisableRange<float>(750.0f, 6000.0f), 1000.0f),
    std::make_unique<AudioParameterFloat>("trebboostcut", "TREBBOOSTCUT", NormalisableRange<float>(0.1f, 2.0f), 1.0f),
    std::make_unique<AudioParameterFloat>("mid", "MID", NormalisableRange<float>(250.0f, 700.0f), 500.0f),
    std::make_unique<AudioParameterFloat>("bass", "BASS", NormalisableRange<float>(20.0f, 250.0f), 200.0f),
    std::make_unique<AudioParameterFloat>("bassboostcut", "BASSBOOSTCUT", NormalisableRange<float>(0.1f, 2.0f), 1.0f))),
    highShelfFilter(dsp::IIR::Coefficients<float>::makeHighShelf(44100, 20000.0f, 1.0f, 1.0f)),
    lowShelfFilter(dsp::IIR::Coefficients<float>::makeLowShelf(44100, 800.0f, 1.0f, 1.0f)),
    midBandPassFilter(dsp::IIR::Coefficients<float>::makeBandPass(44100, 500.0f, 1.0f))

{
    //create log to save setings between uses
    valueTree.state = ValueTree("SavedParameters");
}

MajorProjectAudioProcessor::~MajorProjectAudioProcessor()
{
}

//==============================================================================
const String MajorProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MajorProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MajorProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MajorProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MajorProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MajorProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MajorProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MajorProjectAudioProcessor::setCurrentProgram (int index)
{
}

const String MajorProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void MajorProjectAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MajorProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    lastSampleRate = sampleRate;
    //DSP module added for filter
    dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate; //tie function parameters to dsp
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumInputChannels();
    //setup filter & reset filter to free up memory afterwards
    highShelfFilter.prepare(spec);
    highShelfFilter.reset();
    midBandPassFilter.prepare(spec);
    midBandPassFilter.reset();
    lowShelfFilter.prepare(spec);
    lowShelfFilter.reset();
}

void MajorProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MajorProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MajorProjectAudioProcessor::updateParameters(){
    //update Parameters for processes

    float treb = *valueTree.getRawParameterValue("treb");
    float trebBoostCut = *valueTree.getRawParameterValue("trebboostcut");
    float mid = *valueTree.getRawParameterValue("mid");
    float bass = *valueTree.getRawParameterValue("bass");
    float bassBoostCut = *valueTree.getRawParameterValue("bassboostcut");
    float res = *valueTree.getRawParameterValue("res");
    *highShelfFilter.state = *dsp::IIR::Coefficients<float>::makeHighShelf(lastSampleRate, treb, res, trebBoostCut);
    *midBandPassFilter.state = *dsp::IIR::Coefficients<float>::makeBandPass(lastSampleRate, mid, 1.0f);
    *lowShelfFilter.state = *dsp::IIR::Coefficients<float>::makeLowShelf(lastSampleRate,  bass, res, bassBoostCut);
}

void MajorProjectAudioProcessor::process(dsp::ProcessContextReplacing <float> context){
    //process done here for output
}

void MajorProjectAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    //used for stereo or multichannel to check max channels**DONT TOUCH**
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    //tone filter dsp setup
    dsp::AudioBlock<float> block (buffer);
    updateParameters();
    highShelfFilter.process(dsp::ProcessContextReplacing <float> (block));
    midBandPassFilter.process(dsp::ProcessContextReplacing <float> (block));
    lowShelfFilter.process(dsp::ProcessContextReplacing <float> (block));
    
    //parameters for amp sim
    float volume = valueTree.getParameter("volume")->getValue();
    float gain = valueTree.getParameter("gain")->getValue();
    float presence = valueTree.getParameter("presence")->getValue();
    float master = valueTree.getParameter("master")->getValue();
    float io = valueTree.getParameter("io")->getValue();
    

    //audio processing info
    for (int channel = 0; channel < totalNumInputChannels; ++channel){
        auto* channelData = buffer.getWritePointer (channel);
        //pass each parameter through to create gradual distortion/gain
        for (int i = 0; i < buffer.getNumSamples(); i++){
            //processing input signal
            float cleanSig = channelData[i];
            //input level and distortion of input
            channelData[i] *= volume * gain;
            
            //io decides whether FX is live or not
            if(io == 1){
                //output signal for amp
                channelData[i] = (((((2.0f / float_Pi) * atan((2.0f / float_Pi) * channelData[i] * (buffer.getNumSamples())) * presence)) + (cleanSig * (1 - presence))) * master) * io;
            } else { channelData[i] = cleanSig; }
        }
    }
}

//==============================================================================
bool MajorProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MajorProjectAudioProcessor::createEditor()
{
    return new MajorProjectAudioProcessorEditor (*this);
}

//==============================================================================
void MajorProjectAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // log XML to save values to
    std::unique_ptr  <XmlElement> xml (valueTree.state.createXml());
    copyXmlToBinary(*xml, destData);
}

void MajorProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // recall xml when reopening plugin
    std::unique_ptr  <XmlElement> reloadXml (getXmlFromBinary(data, sizeInBytes));
    if (reloadXml != nullptr){
        if (reloadXml -> hasTagName(valueTree.state.getType())){
            valueTree.state = ValueTree::fromXml(*reloadXml);
        }
    }
    
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MajorProjectAudioProcessor();
}
//==============================================================================
