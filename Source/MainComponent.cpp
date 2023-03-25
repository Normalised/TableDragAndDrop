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

void TrackTableModel::paintCell(juce::Graphics& graphics, int rowNumber, int columnId, int width, int height,
                                bool rowIsSelected)
{
    if(rowNumber < tracks.size()) {
        graphics.setColour(juce::Colours::white);
        graphics.setFont(14.0f);

        auto & track = tracks[rowNumber];
        switch(columnId) {
            case 1: graphics.drawText(track.artist, 0, 0, width, height, juce::Justification::centred, 1); break;
            case 2: graphics.drawText(track.name, 0, 0, width, height, juce::Justification::centred, 1); break;
            case 3: graphics.drawText(track.album, 0, 0, width, height, juce::Justification::centred, 1); break;
        }
    }
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
