
#ifndef FRAME_H
#define FRAME_H

#include <wx/wx.h>

class Frame : public wxFrame
{
public:
    Frame(const wxString& title, const wxPoint& pos, const wxSize& size);
    ~Frame();

    void OnButtonClicked(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAddTask(wxCommandEvent& event);
    void OnDeleteTask(wxCommandEvent& event);

private:
    wxButton* addButton;
    wxButton* deleteButton;
    wxListBox* taskList;

    static const int ID_AddTask = wxID_HIGHEST + 1;
    static const int ID_DeleteTask = wxID_HIGHEST + 2;

    wxDECLARE_EVENT_TABLE();
};

#endif // FRAME_H
