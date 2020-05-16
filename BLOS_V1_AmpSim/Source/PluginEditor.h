/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
class OtherLookAndFeel : public LookAndFeel_V4{
public:
    void drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider &slider) override {
        auto radius = jmin (width / 2, height / 2) - 4.0f;
        auto centreX = x + width  * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        
        // fill
        g.setColour (Colours::black);
        g.fillEllipse (rx, ry, rw, rw);
         
        // outline
        g.setColour (Colours::whitesmoke);
        g.drawEllipse (rx, ry, rw, rw, 2.0f);
        
        Path p;
        auto pointerLength = radius * 0.33f;
        auto pointerThickness = 2.0f;
        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
        
        // pointer
        g.setColour (Colours::whitesmoke);
        g.fillPath (p);
    }
};
//==============================================================================
class OtherLookAndFeelEQ : public LookAndFeel_V4{
public:
    void drawRotarySlider(Graphics &g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, Slider &slider) override {
        auto radius = jmin (width / 2, height / 2) - 4.0f;
        auto centreX = x + width  * 0.5f;
        auto centreY = y + height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        
        // fill
        g.setColour (Colours::whitesmoke);
        g.fillEllipse (rx, ry, rw, rw);
         
        // outline
        g.setColour (Colours::red);
        g.drawEllipse (rx, ry, rw, rw, 2.0f);
        
        Path p;
        auto pointerLength = radius * 0.33f;
        auto pointerThickness = 2.0f;
        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
        
        // pointer
        g.setColour (Colours::red);
        g.fillPath (p);
    }
};
//==============================================================================
class MajorProjectAudioProcessorEditor  : public AudioProcessorEditor,
    public Slider::Listener
{
public:
    MajorProjectAudioProcessorEditor (MajorProjectAudioProcessor&);
    ~MajorProjectAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider *slider) override;
    void buttonClicked(Button *button);

private:
    MajorProjectAudioProcessor& processor;
    
    OtherLookAndFeel otherLookAndFeel;
    OtherLookAndFeelEQ otherLookAndFeelEQ;
    
    //sliders for control dials
    Slider volumeSlider;
    Slider gainSlider;
    Slider presenceSlider;
    Slider masterSlider;
    Slider trebSlider;
    Slider trebBoostCutSlider;
    Slider midSlider;
    Slider bassSlider;
    Slider bassBoostCutSlider;
    Slider resSlider;
    
    TextButton ioButton;
    
    //slider attachment for valueTrees **will destruct first**
    AudioProcessorValueTreeState::SliderAttachment volumeAttach;
    AudioProcessorValueTreeState::SliderAttachment gainAttach;
    AudioProcessorValueTreeState::SliderAttachment presenceAttach;
    AudioProcessorValueTreeState::SliderAttachment masterAttach;
    AudioProcessorValueTreeState::SliderAttachment trebAttach;
    AudioProcessorValueTreeState::SliderAttachment trebBoostCutAttach;
    AudioProcessorValueTreeState::SliderAttachment midAttach;
    AudioProcessorValueTreeState::SliderAttachment bassAttach;
    AudioProcessorValueTreeState::SliderAttachment bassBoostCutAttach;
    AudioProcessorValueTreeState::SliderAttachment resAttach;
    AudioProcessorValueTreeState::ButtonAttachment ioAttach;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MajorProjectAudioProcessorEditor)
};
