Frame .cpp
#include "Frame.h"
#include <wx/listctrl.h>
#include <wx/filedlg.h>
#include <opencv2/opencv.hpp>

#include "SharedResources.h"  // Include shared resources
pthread_mutex_t taskMutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t taskCond = PTHREAD_COND_INITIALIZER;

Frame::Frame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size) {

    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    taskListView = new wxListView(this, wxID_ANY);
    originalImage = new wxStaticBitmap(this, wxID_ANY, wxBitmap(100, 100));
    processedImage = new wxStaticBitmap(this, wxID_ANY, wxBitmap(100, 100));
    filterComboBox = new wxComboBox(this, wxID_ANY, wxT(""));
    logTextCtrl = new wxTextCtrl(this, wxID_ANY, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    updateTimer = new wxTimer(this, ID_UpdateTimer);

    mainSizer->Add(taskListView, 1, wxEXPAND);
    mainSizer->Add(originalImage, 0, wxALIGN_CENTER);
    mainSizer->Add(processedImage, 0, wxALIGN_CENTER);
    mainSizer->Add(filterComboBox, 0, wxALIGN_CENTER);
    mainSizer->Add(logTextCtrl, 0, wxEXPAND);

    // Adding Buttons
    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(new wxButton(this, ID_LoadImage, wxT("Load Image")), 0, wxALL, 5);
    buttonSizer->Add(new wxButton(this, ID_AddTask, wxT("Add Task")), 0, wxALL, 5);
    buttonSizer->Add(new wxButton(this, ID_DeleteTask, wxT("Remove Task")), 0, wxALL, 5);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

    this->SetSizer(mainSizer);

    // Event Bindings
    Bind(wxEVT_BUTTON, &Frame::OnLoadImage, this, ID_LoadImage);
    Bind(wxEVT_BUTTON, &Frame::OnAddTask, this, ID_AddTask);
    Bind(wxEVT_BUTTON, &Frame::OnDeleteTask, this, ID_DeleteTask);
    Bind(wxEVT_TIMER, &Frame::OnTimer, this, ID_UpdateTimer);
}