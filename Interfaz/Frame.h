
#ifndef FRAME_H
#define FRAME_H

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <pthread.h>
#include <vector>
#include <string>
#include "Task.h"

// Estructura para mantener la información de la imagen
struct Image {
    wxBitmap bitmap;
    std::string path;
    // ... puedes añadir más campos si es necesario
};


class Frame : public wxFrame {
public:
    Frame(const wxString& title, const wxPoint& pos, const wxSize& size);
    virtual ~Frame();  // Adding virtual destructor

    void OnExit(wxCommandEvent& event);
    void OnAddTask(wxCommandEvent& event);
    void OnDeleteTask(wxCommandEvent& event);
    void OnLoadImage(wxCommandEvent& event);
    void OnTimer(wxTimerEvent& event);
    std::vector<Task> taskList;


private:
    wxButton* addButton;
    wxButton* deleteButton;
    wxListBox* taskListBox;  // Cambiado el nombre para evitar conflicto
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

    wxDECLARE_EVENT_TABLE();
};

#endif // FRAME_H
