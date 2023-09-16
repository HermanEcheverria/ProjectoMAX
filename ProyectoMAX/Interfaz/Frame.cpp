#include "Frame.h"
#include <wx/listctrl.h>
#include <wx/filedlg.h>
#include <opencv2/opencv.hpp>
#include "SharedResources.h"

std::vector<Task> taskList;
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

    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(new wxButton(this, ID_LoadImage, wxT("Load Image")), 0, wxALL, 5);
    buttonSizer->Add(new wxButton(this, ID_AddTask, wxT("Add Task")), 0, wxALL, 5);
    buttonSizer->Add(new wxButton(this, ID_DeleteTask, wxT("Remove Task")), 0, wxALL, 5);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);
    this->SetSizer(mainSizer);

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

        // Escalar las imágenes para que se ajusten al tamaño de visualización
        wxSize displaySize(400, 400); // Ajusta según tus preferencias
        wxImage scaledOriginal = wxImg.Rescale(displaySize.GetWidth(), displaySize.GetHeight());
        wxBitmap bmpOriginal(scaledOriginal);

        // Aplicar el filtro (en este caso, sepia)
        cv::Mat sepiaImage = applySepiaFilter(img);

        // Convertir la imagen procesada de OpenCV a wxImage
        cv::cvtColor(sepiaImage, sepiaImage, cv::COLOR_BGR2RGB);
        wxImage wxSepiaImage(sepiaImage.cols, sepiaImage.rows, sepiaImage.data, true);
        wxBitmap bmpSepia(wxSepiaImage);

        // La imagen procesada también se escala
        wxImage scaledProcessed = wxSepiaImage.Rescale(displaySize.GetWidth(), displaySize.GetHeight());
        wxBitmap bmpProcessed(scaledProcessed);

        // Mostrar las imágenes escaladas
        originalImage->SetBitmap(bmpOriginal);
        processedImage->SetBitmap(bmpProcessed);
    }

    logTextCtrl->AppendText(wxT("Image Loaded.\n"));
}




cv::Mat Frame::applySepiaFilter(const cv::Mat& src) {
    cv::Mat dst = src.clone();
    for (int y = 0; y < src.rows; ++y) {
        for (int x = 0; x < src.cols; ++x) {
            cv::Vec3b& color = dst.at<cv::Vec3b>(y, x);
            color[0] = cv::saturate_cast<uchar>(color[0]*0.272 + color[1]*0.534 + color[2]*0.131); // Blue
            color[1] = cv::saturate_cast<uchar>(color[0]*0.349 + color[1]*0.686 + color[2]*0.168); // Green
            color[2] = cv::saturate_cast<uchar>(color[0]*0.393 + color[1]*0.769 + color[2]*0.189); // Red
        }
    }
    return dst;
}

void Frame::OnAddTask(wxCommandEvent& event) {
    Task newTask;
    wxString selectedFilter = filterComboBox->GetValue();
    newTask.filterType = selectedFilter.ToStdString();
    taskList.push_back(newTask);

    wxFileDialog openFileDialog(this, wxT("Open Image file"), "", "",
                               "Image files (*.jpg;*.png)|*.jpg;*.png", wxFD_OPEN|wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }

    wxString path = openFileDialog.GetPath();
    cv::Mat img = cv::imread(path.ToStdString());

    if (!img.empty()) {
        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
        wxImage wxImg(img.cols, img.rows, img.data, true);
        wxBitmap bmp(wxImg);

        wxSize displaySize(200, 200);
        wxImage scaledOriginal = wxImg.Rescale(displaySize.GetWidth(), displaySize.GetHeight());
        wxBitmap bmpOriginal(scaledOriginal);

        cv::Mat sepiaImage = applySepiaFilter(img);

        cv::cvtColor(sepiaImage, sepiaImage, cv::COLOR_BGR2RGB);
        wxImage wxSepiaImage(sepiaImage.cols, sepiaImage.rows, sepiaImage.data, true);
        wxBitmap bmpSepia(wxSepiaImage);

        wxImage scaledProcessed = wxSepiaImage.Rescale(displaySize.GetWidth(), displaySize.GetHeight());
        wxBitmap bmpProcessed(scaledProcessed);

        originalImage->SetBitmap(bmpOriginal);
        processedImage->SetBitmap(bmpProcessed);
    }

    logTextCtrl->AppendText(wxT("Image Loaded.\n"));
}

void Frame::OnDeleteTask(wxCommandEvent& event) {
    logTextCtrl->AppendText(wxT("Delete Task button pressed.\n"));

    if (taskList.empty()) {
        logTextCtrl->AppendText(wxT("No tasks to delete.\n"));
        return;
    }

    pthread_mutex_lock(&taskMutex);
    taskList.pop_back();
    pthread_mutex_unlock(&taskMutex);
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
