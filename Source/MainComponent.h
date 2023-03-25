#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

struct Player : juce::Component, juce::DragAndDropTarget {
    Player() {
        addAndMakeVisible(trackName);
        trackName.setColour(juce::Label::ColourIds::textColourId, juce::Colours::yellow);
        trackName.setFont(32.0f);
    }
    void paint(juce::Graphics &g) override {
        g.fillAll(juce::Colours::black);
    }

    bool isInterestedInDragSource(const SourceDetails &dragSourceDetails) override {
        return true;
    }

    void itemDropped(const SourceDetails &dragSourceDetails) override {
        trackName.setText(dragSourceDetails.description, juce::dontSendNotification);
    }

    void resized() override {
        trackName.setBounds(getLocalBounds());
    }

    juce::Label trackName;
};

struct TrackData {
    juce::String artist;
    juce::String name;
    juce::String album;
};

struct TrackTableModel : juce::TableListBoxModel {

    TrackTableModel();

    int getNumRows() override;
    void paintRowBackground(juce::Graphics& graphics, int rowNumber, int width, int height,
                            bool rowIsSelected) override;
    void paintCell(juce::Graphics& graphics, int rowNumber, int columnId, int width, int height,
                   bool rowIsSelected) override {}

    juce::var getDragSourceDescription(const juce::SparseSet<int>& currentlySelectedRows) override {
        if(!currentlySelectedRows.isEmpty()) {
            auto track = tracks[currentlySelectedRows[0]];
            return track.name;
        }
    }

    juce::Component * refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, juce::Component *existingComponentToUpdate) override {
        juce::Label* label = nullptr;
        if(existingComponentToUpdate == nullptr) {
            label = new juce::Label();
            label->setInterceptsMouseClicks(false, false);
        } else {
            label = dynamic_cast<juce::Label*>(existingComponentToUpdate);
        }
        auto & track = tracks[rowNumber];
        switch(columnId) {
            case 1: label->setText(track.artist, juce::dontSendNotification); break;
            case 2: label->setText(track.name, juce::dontSendNotification); break;
            case 3: label->setText(track.album, juce::dontSendNotification); break;
        }
        return label;
    }
    std::vector<TrackData> tracks;
};

class MainComponent : public juce::Component, public juce::DragAndDropContainer
{
public:
    //==============================================================================
    MainComponent();

    //==============================================================================
    void resized() override;

private:

    juce::TableListBox tableView {};
    TrackTableModel tableModel {};

    Player playerView;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
