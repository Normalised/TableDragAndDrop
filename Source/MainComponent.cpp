#include "MainComponent.h"

MainComponent::MainComponent()
{
    setSize(800, 600);
    tableView.getHeader().addColumn("Artist",1, 250);
    tableView.getHeader().addColumn("Track",2, 250);
    tableView.getHeader().addColumn("Album",3, 250);
    tableView.setModel(&tableModel);
    tableView.updateContent();
    addAndMakeVisible(tableView);
    addAndMakeVisible(playerView);
}

void MainComponent::resized()
{
    tableView.setBounds(0, 0, 750, 400);
    playerView.setBounds(0,400, 600, 200);
}
int TrackTableModel::getNumRows()
{
    return tracks.size();
}
void TrackTableModel::paintRowBackground(juce::Graphics& graphics, int rowNumber, int width, int height,
                                         bool rowIsSelected)
{
    graphics.fillAll(juce::Colours::black);
}

TrackTableModel::TrackTableModel()
{
    TrackData giantSteps = {"John Coltrane", "Countdown", "Giant Steps"};
    TrackData hardToEarn = {"Gang Starr", "Mass Appeal", "Hard To Earn"};
    TrackData quintessence = {"Dark Throne", "Quintessence", "Panzerfaust"};

    tracks.push_back(giantSteps);
    tracks.push_back(hardToEarn);
    tracks.push_back(quintessence);
}
juce::Component* TrackTableModel::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected,
                                                          juce::Component* existingComponentToUpdate)
{
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
juce::var TrackTableModel::getDragSourceDescription(const juce::SparseSet<int>& currentlySelectedRows)
{
    if(!currentlySelectedRows.isEmpty()) {
        auto track = tracks[currentlySelectedRows[0]];
        return track.name;
    }
}
