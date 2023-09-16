
#ifndef FRAME_H
#define FRAME_H
#include <opencv2/opencv.hpp>
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <pthread.h>
#include <vector>
#include <string>
#include "Task.h"

class Frame : public wxFrame {
public:
    Frame(const wxString& title, const wxPoint& pos, const wxSize& size);
    ~Frame();

    void OnLoadImage(wxCommandEvent& event);
    void OnAddTask(wxCommandEvent& event);
    void OnDeleteTask(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);

private:
    wxListView* taskListView;
    wxStaticBitmap* originalImage;
    wxStaticBitmap* processedImage;
    wxComboBox* filterComboBox;
    wxTextCtrl* logTextCtrl;
    wxTimer* updateTimer;
    static const int ID_AddTask = wxID_HIGHEST + 1;
    static const int ID_DeleteTask = wxID_HIGHEST + 2;
    static const int ID_LoadImage = wxID_HIGHEST + 3;
    static const int ID_UpdateTimer = wxID_HIGHEST + 4;  // Identificador para el wxTimer
    cv::Mat applySepiaFilter(const cv::Mat& src);
    wxDECLARE_EVENT_TABLE();
};

#endif // FRAME_H
