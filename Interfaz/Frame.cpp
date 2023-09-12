
#include "Frame.h"

wxBEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_BUTTON(ID_AddTask, Frame::OnAddTask)
    EVT_BUTTON(ID_DeleteTask, Frame::OnDeleteTask)
    EVT_BUTTON(wxID_EXIT, Frame::OnExit)
wxEND_EVENT_TABLE()

Frame::Frame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    wxPanel* panel = new wxPanel(this, -1);

    addButton = new wxButton(panel, ID_AddTask, wxT("Agregar Tarea"), wxPoint(170, 10));
    deleteButton = new wxButton(panel, ID_DeleteTask, wxT("Eliminar Tarea"), wxPoint(170, 50));
    taskList = new wxListBox(panel, -1, wxPoint(10, 10), wxSize(150, 100));

    Centre();
}

Frame::~Frame()
{

}

void Frame::OnButtonClicked(wxCommandEvent& event)
{
    // Manejar el evento de botón aquí
}

void Frame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void Frame::OnAddTask(wxCommandEvent& event)
{
    wxString name;
    wxTextEntryDialog dialog(this, "Ingrese el nombre de la tarea:", "Nueva Tarea");

    if (dialog.ShowModal() == wxID_OK)
    {
        name = dialog.GetValue();
        if (!name.IsEmpty())
        {
            // Agregar la tarea a la lista
            taskList->Append(name);
        }
    }
}


void Frame::OnDeleteTask(wxCommandEvent& event)
{
    int selectedItem = taskList->GetSelection();
    if (selectedItem != wxNOT_FOUND)
    {
        taskList->Delete(selectedItem);
    }
}
