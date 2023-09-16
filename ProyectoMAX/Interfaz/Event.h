#ifndef EVENT_H
#define EVENT_H

#include <wx/event.h>

// Definir un nuevo tipo de evento para agregar tareas
wxDECLARE_EVENT(wxEVT_ADD_TASK, wxCommandEvent);

// Definir un nuevo tipo de evento para eliminar tareas
wxDECLARE_EVENT(wxEVT_DELETE_TASK, wxCommandEvent);

#endif // EVENT_H


