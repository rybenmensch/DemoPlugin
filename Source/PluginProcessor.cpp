/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DemoPluginAudioProcessor::DemoPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    //nothing else to be done in the constructor

}

DemoPluginAudioProcessor::~DemoPluginAudioProcessor(){

}

//==============================================================================
const juce::String DemoPluginAudioProcessor::getName() const{
    return JucePlugin_Name;
}

bool DemoPluginAudioProcessor::acceptsMidi() const{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DemoPluginAudioProcessor::producesMidi() const{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DemoPluginAudioProcessor::isMidiEffect() const{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DemoPluginAudioProcessor::getTailLengthSeconds() const{
    return 0.0;
}

int DemoPluginAudioProcessor::getNumPrograms(){
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DemoPluginAudioProcessor::getCurrentProgram(){
    return 0;
}

void DemoPluginAudioProcessor::setCurrentProgram (int index){
}

const juce::String DemoPluginAudioProcessor::getProgramName (int index){
    return {};
}

void DemoPluginAudioProcessor::changeProgramName (int index, const juce::String& newName){
}

//==============================================================================
void DemoPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock){
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void DemoPluginAudioProcessor::releaseResources(){
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DemoPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void DemoPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages){
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    int frames = buffer.getNumSamples();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, frames);
    
    AudioBuffer<float> input(1, frames);
    input.copyFrom(0, 0, buffer, 0, 0, frames);
    const float* read = input.getReadPointer(0);
   
    /*ambisonics*/
    // get snapshot of current AED coordinates and convert angles from degrees to radians
    float pi = MathConstants<float>::pi;
    float a = -audioParams.a->get() * pi / 180.0f; // our azimuth is in Navigation direction (clockwise), in mathematics we need conter-clock-wise!
    float e = audioParams.e->get() * pi / 180.0f;
    float d = audioParams.d->get();
    
    // calculate distance attenuations
    float unitCircle = 0.1f;
    float scaledDistance = jmax(unitCircle, d * (1.0f / unitCircle));
    float distanceFactorW = atan(scaledDistance * pi / 2.0f) / (scaledDistance * pi / 2.0f);
    float distanceFactorOthers = (1 - exp(-scaledDistance)) * distanceFactorW;
    
    // calculate ambisonics (B-format) factors
    float ambiFactors[4];
    ambiFactors[0] = distanceFactorW * 1.0f;
    ambiFactors[1] = distanceFactorOthers * cos(e) * sin(a);
    ambiFactors[2] = distanceFactorOthers * sin(e);
    ambiFactors[3] = distanceFactorOthers * cos(e) * cos(a);
    
    for (int channel = 0; channel < totalNumOutputChannels; ++channel){
        
        auto *channelData = buffer.getWritePointer(channel);

        for(int i=0;i<frames;i++){
            float factor = ambiFactors[channel];
            channelData[i] = read[i] * factor;
        }
    }
}

//==============================================================================
bool DemoPluginAudioProcessor::hasEditor() const{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DemoPluginAudioProcessor::createEditor(){
    return new DemoPluginAudioProcessorEditor (*this);
}

//==============================================================================
void DemoPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData){
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DemoPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes){
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter(){
    return new DemoPluginAudioProcessor();
}
