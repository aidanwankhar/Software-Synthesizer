/*
  ==============================================================================

    FilterComponent.cpp
    Created: 4 Jul 2024 3:48:40pm
    Author:  Aidan

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================
FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeSelectorId, juce::String filterCutoffId, juce::String filterResId)
{
    juce::StringArray choices { "Low-Pass", "Band-Pass", "High-Pass" };
    filterTypeSelector.addItemList(choices, 1);
    addAndMakeVisible(filterTypeSelector);

    filterTypeSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filterTypeSelectorId, filterTypeSelector);

    filterSelectorLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    filterSelectorLabel.setFont(15.0f);
    filterSelectorLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(filterSelectorLabel);


    setSliderWithLabel(filterCutoffSlider, filterCutoffLabel, apvts, filterCutoffId, filterCutoffAttachment);
    setSliderWithLabel(filterResonanceSlider, filterResLabel, apvts, filterResId, filterResAttachment);

}

FilterComponent::~FilterComponent()
{
}

void FilterComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.fillAll(juce::Colour(23, 19, 11));
    g.setColour(juce::Colours::burlywood);
    g.setFont(20.0f);
    g.drawText("Filter", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
}

void FilterComponent::resized()
{
    const auto startY = 55;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelYOffset = 20;
    const auto labelHeight = 20;

    filterTypeSelector.setBounds(10, startY + 5, 90, 30);
    filterSelectorLabel.setBounds(10, startY - labelYOffset, 90, labelHeight);

    filterCutoffSlider.setBounds(filterTypeSelector.getRight(), startY, sliderWidth, sliderHeight);
    filterCutoffLabel.setBounds(filterCutoffSlider.getX(), filterCutoffSlider.getY() - labelYOffset, filterCutoffSlider.getWidth(), labelHeight);

    filterResonanceSlider.setBounds(filterCutoffSlider.getRight(), startY, sliderWidth, sliderHeight);
    filterResLabel.setBounds(filterResonanceSlider.getX(), filterResonanceSlider.getY() - labelYOffset, filterResonanceSlider.getWidth(), labelHeight);

}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void FilterComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramID, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    getLookAndFeel().setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::darkslategrey);
    getLookAndFeel().setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::cornsilk);
    addAndMakeVisible(slider);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramID, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::burlywood);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}
