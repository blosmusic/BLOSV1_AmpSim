/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MajorProjectAudioProcessorEditor::MajorProjectAudioProcessorEditor
    (MajorProjectAudioProcessor& p) : AudioProcessorEditor (&p), processor (p),
    volumeAttach(processor.valueTree, "volume", volumeSlider),
    gainAttach(processor.valueTree, "gain", gainSlider),
    presenceAttach(processor.valueTree, "presence", presenceSlider),
    masterAttach(processor.valueTree, "master", masterSlider),
    trebAttach(processor.valueTree, "treb", trebSlider),
    trebBoostCutAttach(processor.valueTree, "trebboostcut", trebBoostCutSlider),
    midAttach(processor.valueTree, "mid", midSlider),
    bassAttach(processor.valueTree, "bass", bassSlider),
    bassBoostCutAttach(processor.valueTree, "bassboostcut", bassBoostCutSlider),
    resAttach(processor.valueTree, "res", resSlider),
    ioAttach(processor.valueTree, "io", ioButton)
{
    //vst demensions
    setSize (600, 250);
    //slider parameters and layout
    volumeSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(volumeSlider);
    
    gainSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(gainSlider);
    
    presenceSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(presenceSlider);
    
    masterSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(masterSlider);
    //EQ
    trebSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(trebSlider);
    
    trebBoostCutSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(trebBoostCutSlider);
    
    midSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(midSlider);
    
    bassSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(bassSlider);
    
    bassBoostCutSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(bassBoostCutSlider);
    
    resSlider.setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    addAndMakeVisible(resSlider);
    //power button
    ioButton.setColour(TextButton::ColourIds::buttonColourId, Colours::darkred);
    ioButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::red);
    ioButton.setClickingTogglesState(true);
    ioButton.onClick = [this]() {};
    addAndMakeVisible(ioButton);
    //look and feel for sliders
    volumeSlider.setLookAndFeel(&otherLookAndFeel);
    gainSlider.setLookAndFeel(&otherLookAndFeel);
    presenceSlider.setLookAndFeel(&otherLookAndFeel);
    masterSlider.setLookAndFeel(&otherLookAndFeel);
    resSlider.setLookAndFeel(&otherLookAndFeel);
    
    bassSlider.setLookAndFeel(&otherLookAndFeelEQ);
    bassBoostCutSlider.setLookAndFeel(&otherLookAndFeelEQ);
    midSlider.setLookAndFeel(&otherLookAndFeelEQ);
    trebSlider.setLookAndFeel(&otherLookAndFeelEQ);
    trebBoostCutSlider.setLookAndFeel(&otherLookAndFeelEQ);
    
    
}

MajorProjectAudioProcessorEditor::~MajorProjectAudioProcessorEditor()
{
}

//==============================================================================
void MajorProjectAudioProcessorEditor::paint (Graphics& g)
{
    //graphics
    //BLACK (background)
    g.fillAll (Colours::black);
    //WHITESMOKE (outline)
    g.setColour (Colours::whitesmoke);
    g.drawRect(5, 5, 590, 240);
    g.drawLine(5, 150, 595, 150);
    //TRANSPARENT DARKGREY (interface)
    g.setColour (Colours::dimgrey);
    g.fillRect(10, 10, 580, 135);
    //WHITE (interface outlines)
    //input section
    g.setFont (15.0f);
    g.setColour (Colours::whitesmoke);
    g.drawFittedText("INPUT", 30, 7, 150, 30, Justification::left, 1);
    g.drawLine(30, 30, 150, 30);
    g.drawLine(30, 30, 30, 35);
    g.setFont (12.0f);
    g.drawFittedText("-VOLUME-", 30, 70, 50, 50, Justification::horizontallyCentred , 1);
    g.drawFittedText("-GAIN-", 90, 70, 50, 50, Justification::horizontallyCentred , 1);
    //eq section
    g.setFont (15.0f);
    g.drawFittedText("EQUALISATION", 155, 7, 400, 30, Justification::left, 1);
    g.drawLine(155, 30, 400, 30);
    g.drawLine(155, 30, 155, 35);
    g.setFont (12.0f);
    g.drawFittedText("BASS", 145, 50, 50, 50, Justification::horizontallyCentred , 1);
    g.drawFittedText("-CUT-", 215, 70, 50, 50, Justification::horizontallyCentred , 1);
    g.drawFittedText("MID", 215, 50, 50, 50, Justification::horizontallyCentred , 1);
    g.drawFittedText("TREB", 285, 50, 50, 50, Justification::horizontallyCentred , 1);
    g.drawFittedText("-RESONANCE-", 340, 70, 50, 50, Justification::horizontallyCentred , 1);
    //master section
    g.setFont (15.0f);
    g.drawFittedText("MASTER", 405, 7, 525, 30, Justification::left, 1);
    g.drawLine(405, 30, 525, 30);
    g.drawLine(405, 30, 405, 35);
    g.setFont (12.0f);
    g.drawFittedText("-PRESENCE-", 405, 70, 50, 50, Justification::horizontallyCentred , 1);
    g.drawFittedText("-MASTER-", 470, 70, 50, 50, Justification::horizontallyCentred , 1);
    //Title Text
    g.setFont (70.0f);
    g.setColour (Colours::snow);
    g.drawFittedText ("BLOS", 10, 160, 595, 160, Justification::topLeft, 1);
    g.setFont (50.0f);
    g.drawFittedText ("V1", 535, 100, 50, 60, Justification::topLeft, 1);
//==============================================================================
}

void MajorProjectAudioProcessorEditor::resized()
{
    //slider parameters
    volumeSlider.setBounds(25, 30, 60, 60);
    volumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    gainSlider.setBounds(85, 30, 60, 60);
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    
    presenceSlider.setBounds(400, 30, 60, 60);
    presenceSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    masterSlider.setBounds(465, 30, 60, 60);
    masterSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    
    bassSlider.setBounds(150, 30, 40, 40);
    bassSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    bassBoostCutSlider.setBounds(185, 60, 40, 40);
    bassBoostCutSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    
    midSlider.setBounds(220, 30, 40, 40);
    midSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    
    trebSlider.setBounds(290, 30, 40, 40);
    trebSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    trebBoostCutSlider.setBounds(255, 60, 40, 40);
    trebBoostCutSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    
    resSlider.setBounds(335, 30, 60, 60);
    resSlider.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    //power button
    ioButton.setBounds(535, 15, 50, 60);
}

void MajorProjectAudioProcessorEditor::sliderValueChanged(Slider *slider){

}

void MajorProjectAudioProcessorEditor::buttonClicked(Button *button){
}
