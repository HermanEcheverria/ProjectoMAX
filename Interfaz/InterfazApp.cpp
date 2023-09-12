/***************************************************************
 * Name:      InterfazApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Herman  ()
 * Created:   2023-09-11
 * Copyright: Herman  ()
 * License:
 **************************************************************/

#include "wx/wx.h"
#include "InterfazApp.h"
#include "Frame.h"

IMPLEMENT_APP(InterfazApp);

bool InterfazApp::OnInit()
{
    Frame* frame = new Frame(wxT("Gestor de Tareas"), wxPoint(50, 50), wxSize(800, 600));
    frame->Show(true);
    return true;
}

