//---------------------------------------------------------------------------
#include <vcl.h>
#include <SysUtils.hpp>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1* Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)  : TForm(Owner)  {}
//---------------------------------------------------------------------------


class CustData{
	private:
		System::String id  ;
		System::String name;
		System::String addr;

	protected:
		System::String readid()                {  return (id);     }
		System::String readname()              {  return (name);   }
		System::String readaddr()              {  return (addr);   }

		void writeid  (System::String newid)   {  if (id == "") { id = newid; }  }
		void writename(System::String newname) {  name = newname; 	}
		void writeaddr(System::String newaddr) {  addr = newaddr;   }

	public:
		CustData() = default;
		//CustData( System::String newid, System::String newnm, System::String newaddr ) ;

		__property
		System::String cid   = {read = readid,   write = writeid  };
		__property
		System::String cname = {read = readname, write = writename};
		__property
		System::String caddr = {read = readaddr, write = writeaddr};
};

CustData Customers[11];
int      NoCusts = 0;

void DisplayCustomer(CustData& c) {

	   Form1->Memo1->Clear();

	   Form1->Memo1->Lines->Add( "" );
	   Form1->Memo1->Lines->Add( "Cust Id : " + c.cid   );
	   Form1->Memo1->Lines->Add( "" );
	   Form1->Memo1->Lines->Add( "Name : "    + c.cname );
	   Form1->Memo1->Lines->Add( "" );
	   Form1->Memo1->Lines->Add( "Address : " + c.caddr );
}

void __fastcall TForm1::Button3Click(TObject *Sender)
{
	   // New customer
	   if (NoCusts < 10) {
			++NoCusts;
			Customers[NoCusts]          = CustData( );
			Form1->Label1->Caption      = IntToStr( NoCusts );
			Customers[NoCusts].cid      = IntToStr( NoCusts );
			if (Form1->ScrollBar1->Position != NoCusts)
				Form1->ScrollBar1->Position = NoCusts;
			else
				DisplayCustomer( Customers[NoCusts] );
	   }
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
	// Change name
		Form2->ShowModal();

		int x = Form1->ScrollBar1->Position;
		if (x <= NoCusts) {
			Customers[ x ].cname = Form2->Edit1->Text;
			DisplayCustomer( Customers[ x ] );
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	// Change address
		Form3->ShowModal();

		int x = Form1->ScrollBar1->Position;
		if (x <= NoCusts) {
			Customers[ x ].caddr = Form3->Edit1->Text;
			DisplayCustomer( Customers[ x ] );
		}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ScrollBar1Change(TObject *Sender)
{
		DisplayCustomer( Customers[ Form1->ScrollBar1->Position ] );
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
		Customers[0].cid   = "0";
		Customers[0].cname = "Record Zero";
		Customers[0].caddr = "-----------";
		DisplayCustomer( Customers[0] );
}
//---------------------------------------------------------------------------

