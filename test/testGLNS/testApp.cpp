/***************************************************************
 * Name:      testApp.cpp
 * Purpose:   Code for Application Class
 * Author:    b ()
 * Created:   2020-06-08
 * Copyright: b ()
 * License:
 **************************************************************/

#include "testApp.h"

//(*AppHeaders
#include "testMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(testApp);

bool testApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	testDialog Dlg(0);
    	SetTopWindow(&Dlg);
    	Dlg.ShowModal();
    	wxsOK = false;
    }
    //*)
    return wxsOK;

}
