/***************************************************************
 * Name:      dataApp.cpp
 * Purpose:   Code for Application Class
 * Author:    aaa ()
 * Created:   2019-08-14
 * Copyright: aaa ()
 * License:
 **************************************************************/

#include "include/dataApp.h"

//(*AppHeaders
#include "dataMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(dataApp);

bool dataApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	dataDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
