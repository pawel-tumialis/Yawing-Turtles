//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Menus.hpp>
#include <FMX.Dialogs.hpp>
//---------------------------------------------------------------------------
class TMainWindow : public TForm
{
__published:	// IDE-managed Components
	TOpenDialog *OpenDialog1;
	TSaveDialog *SaveDialog1;
	TMainMenu *MainMenu1;
	TMenuItem *Info;
	TMenuItem *Authors;
	TMenuItem *Project;
	TLabel *Label3;
	TButton *Button1;
	TButton *Button2;
	TButton *Button3;
	void __fastcall AuthorsClick(TObject *Sender);
	void __fastcall ProjectClick(TObject *Sender);
	void __fastcall RunClick(TObject *Sender);
	void __fastcall LoadClick(TObject *Sender);
	void __fastcall SaveClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TMainWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainWindow *MainWindow;
//---------------------------------------------------------------------------
#endif
