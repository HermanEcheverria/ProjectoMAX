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

Frame::~Frame() {
    // Destructor code here
}

void Frame::OnLoadImage(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, wxT("Open Image file"), "", "",
                               "Image files (*.jpg;*.png)|*.jpg;*.png", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString path = openFileDialog.GetPath();
    cv::Mat img = cv::imread(path.ToStdString());

    if (!img.empty()) {
        // Convertir la imagen de OpenCV a wxImage
        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
        wxImage wxImg(img.cols, img.rows, img.data, true);
        wxBitmap bmp(wxImg);

        // Mostrar la imagen
        originalImage->SetBitmap(bmp);
    }

    logTextCtrl->AppendText(wxT("Image Loaded.\n"));
    }
void Frame::OnAddTask(wxCommandEvent& event) {
    Task newTask;
    wxString selectedFilter = filterComboBox->GetValue();
    newTask.filterType = selectedFilter.ToStdString();
    taskList.push_back(newTask);
    logTextCtrl->AppendText(wxT("Task added.\n"));
}

void Frame::OnDeleteTask(wxCommandEvent& event) {
    logTextCtrl->AppendText(wxT("Task removed.\n"));
}

void Frame::OnTimer(wxTimerEvent& event) {
    // Code to update the UI
}

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_TIMER(ID_UpdateTimer, Frame::OnTimer)
    EVT_BUTTON(ID_LoadImage, Frame::OnLoadImage)
    EVT_BUTTON(ID_AddTask, Frame::OnAddTask)
    EVT_BUTTON(ID_DeleteTask, Frame::OnDeleteTask)
wxEND_EVENT_TABLE()
