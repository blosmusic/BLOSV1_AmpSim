# BLOSV1_AmpSim

This plugin simulates the basic structure of a guitar amp.

This contains the V1 Guitar Amp Simulator.

### INSTALLATION

To install & use, place the VST file into the plugin directory of your chosen DAW.

In your chosen DAW, add the VST to your signal chain.

Set your parameters and play!

NOTE: Some DAWs may require you to refresh the VST path before using.

### GENERAL

These plugins take audio as input, you can use existing audio samples or place into your recording chain

### BLOS V1 - Guitar Amp Simulator

This plugin simulates the basic structure of a guitar amp. The input section, volume & gain, set the input levels for the audio in use. The presence & master dials control the output levels. The master dial controlls the overall volume. The presence dial blends the input section with the audio passing through, turning this dial up acts in similar fashion to a boost or overdrive. The equalisation section offers the user full scope over their tone. Bass controls frequencies up to 250Hz. Mid boosts between 250-700Hz. Treb controls frequencies over 750Hz. Both bass & treb have a cut/boost dial to further hone the users tone. Lowering these thresholds can be done to create a bass amp sim also.

### DEMO

A demonstration of the VSTs can be found [here](https://www.youtube.com/watch?v=gu4198DzCO4&t=1s).

### HOW IT WORKS

Taking audio as input, the V1 is a basic amp simulator with a full array of controls typically found on amplifiers. The input/output gain and volume staging dials act as the gain and saturation controls of the audio. Using the input and gain together in a similar fashion to a regular guitar amplifier so the user can get the desired sound. The range is that of a boosted clean tone to a distorted sound. Adding the presence control will blend more of the input parameters with the audio signal akin to that of a channel bost or tube screamer effect.

The processing for this is achieved in the processBlock (PluginProcessor.cpp) where the input/output dials are called for using each parameters valueTree. The valueTree for each parameter ties the required parameter with the respective GUI control. In addition, the inclusion and state of the I/O button give the user the option to either use the VST or bypass it in their signal chain as per their use. To prevent feedback and clipping the arctan processing formula was used as this function will always remain between ± pi radians.

In addition, a full range of equalisation parameters is used to allow the user full control over the output sound. As is typical in amplifier manufacturing the bass and treble controls are based on a low and high shelf filter respectively with the middle dial filter utilising a bandpass in-between. The EQ can be further tweaked using the resonance and boost/cut dials. For each of the bass and treble boost/cut dials a value less than 1.0f will cut the frequency whereas a value greater than 1.0f will boost. Each dial is set with a range of 0.1 - 2.0f. The EQ section was completed using JUCE's DSP classes and through the use of IIR (infinite impulse response) due to their understood efficiency.

For ease of use, the XML code in setStateInformation (PluginProcessor.cpp) is used to retain the VSTs settings between sessions or uses. 

The GUI is setup up to mirror a typical guitar amplifier outline with the input, output, and equalisation dials together and marked as such. The GUI also includes a custom slider class which makes the VST appear more like amp dials as described.

### CONTRIBUTING

If you would like to contribute to this repository, please contact me first via [email](hi@benlambosullivan.com).
This repository does not include the builds folder for JUCE, as such contributions would need to be built via Projucer first.

### LICENSE

This project was developed under the [General Public License (GNU)](https://www.gnu.org/licenses/gpl-3.0.en.html).

### ACKNOWLEDGEMENTS

These VSTs were developed for submission as part of a submission for the [Masters in Music Technology](https://www.dkit.ie/courses/school-of-informatics-and-creative-arts/creative-arts-media-and-music/ma/msc-in-music-technology.html) in Dundalk Institute of Technology, Ireland.

Special thanks to the courses lecturer Rory Walsh for his help & input.

Further resources which assisted the development of this project:

[The Audio Programmer YouTube Channel](https://www.youtube.com/theaudioprogrammer)

[JUCE Tutorials](https://juce.com/learn/tutorials)



