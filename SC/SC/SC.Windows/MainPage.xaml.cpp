//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include <CWinsock.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <CommCtrl.h>
#include <algorithm>
#include <winnt.h>
#include <tlhelp32.h>
#include <shlwapi.h>
#include <iostream>
#include <string>
#include <mmsystem.h>
#include <WinInet.h>
#include <time.h>
#include <vector>
#include <debugapi.h>
#include <stdlib.h>  
#include <Winternl.h>
#include <Iphlpapi.h>
#include <VersionHelpers.h>
#include <ShlObj.h>
#include <fstream>
#include <DbgHelp.h>
#include <Psapi.h>
#include <utility>
#include <sstream>
#include <stdio.h>
#include <stdarg.h>
#include <thread>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#include <winuser.h>
#ifndef UNICODE
#define UNICODE
#endif

using namespace SC;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Popups;
bool bIsConnected = false;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238

MainPage::MainPage()
{
	InitializeComponent();

	if (!bIsConnected)
		chatdata->Text = "Not Connected.\n";

	

}


void SC::MainPage::TextBlock_SelectionChanged_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}
/*http://stackoverflow.com/questions/154536/encode-decode-urls-in-c*/
std::string urlEncode(std::string str) { //ß ist halt broken lol
	std::string new_str = "";
	char c;
	int ic;
	const char* chars = str.c_str();
	char bufHex[10];
	int len = strlen(chars);
	for (int i = 0; i<len; i++) {
		c = chars[i];
		ic = c;
		if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') new_str += c;
		else {
			sprintf(bufHex, "%X", c);
			if (ic < 16)
				new_str += "%0";
			else
				new_str += "%";
			new_str += bufHex;
		}
	}
	return new_str;
}

void SC::MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e) //sending
{
	
	if (chatdata && chatbox11 && chatbox11->Text && bIsConnected) {

		UpdateChat();
		


		char buffer[4096] = "";
		char TextData[4096] = "";
		if (sizeof(chatbox11->Text->Data()) > 4096) {
			return;
		}
		wcstombs(TextData, chatbox11->Text->Data(), chatbox11->Text->Length() +1);

		std::string tmpString = TextData;
		if (tmpString.length() > 4096) {
			return;
		}
		tmpString = urlEncode(tmpString);
		

		sprintf_s(buffer, "hwid=777&message=%s", tmpString.c_str());
		g_Winsock.InitWinsock();
		g_Winsock.Connect("sc.r4p1d.xyz");
		g_Winsock.SendHttpGet("http://sc.r4p1d.xyz/chat.php", buffer);
		g_Winsock.Disconnect();
		g_Winsock.CleanUp();

		/*delete[] buffer;
		delete[] TextData;*/


		chatdata->Text += "Ich: " + chatbox11->Text + "\n";
		chatbox11->Text = "";
	}
	
	
}


void SC::MainPage::chatdata_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

}


void SC::MainPage::chatstring_TextChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::TextChangedEventArgs^ e)
{
	
}

void SC::MainPage::UpdateChat() { //ChatUpdating

		if (bIsConnected) {
			g_Winsock.InitWinsock();
			g_Winsock.Connect("sc.r4p1d.xyz");
			std::string chatString = g_Winsock.SendHttpGet("http://sc.r4p1d.xyz/chat.php", "hwid=777");
			g_Winsock.Disconnect();
			g_Winsock.CleanUp();
			if (chatString.length() > 0) {
				std::wstring wid_str = std::wstring(chatString.begin(), chatString.end());
				const wchar_t* w_char = wid_str.c_str();

				Platform::String^ toChat = ref new Platform::String(w_char);

				chatdata->Text += "Partner: " + toChat + "\n";
			}
			
			

		}
		
		

	
}

void SC::MainPage::Button_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)//Connecting
{

	
	if (ort->SelectedIndex >= 0 && aktivitaeten->SelectedIndex >= 0) {
		
		bIsConnected = true;
		chatdata->Text = "";
		chatdata->Text += "Überlege immer, mit wem und wo du dich triffst.\n";
		chatdata->Text += "\n";
		std::string httpString;
		

		//std::vector<Platform::String^> selectedName = { "Kino", "Essen", "Fahrradfahren", "Party", "Chillen" , "LAN-Party" , "Fußball" , "Tennis" , "Volleyball" , "Basketball", "Spazieren gehen" , "Reiten" , "Yoga" };
		//std::vector<Platform::String^> selectedPlace = {"Flensburg", "Kiel", "Lübeck" , "Kaltenkirchen" , "Norderstedt" , "Neumünster" , "Hamburg" , "Itzehoe" , "Quickborn" , "Westerland" , "Fehmarn" , "Schleswig" , "Husum" , "Sant Peter-Ording" , "Wacken" , "Rendsburg" };
		//chatdata->Text += selectedName.at(aktivitaeten->SelectedIndex) + "\n";
		//chatdata->Text += selectedPlace.at(ort->SelectedIndex) + "\n";
		char buffer[256];
		sprintf(buffer, "hwid=777&reset=1&town=%i&act=%i", ort->SelectedIndex, aktivitaeten->SelectedIndex);
		g_Winsock.InitWinsock();
		g_Winsock.Connect("sc.r4p1d.xyz");
		std::string sConnected = g_Winsock.SendHttpGet("http://sc.r4p1d.xyz/chat.php", buffer);
		g_Winsock.Disconnect();
		g_Winsock.CleanUp();

		if (sConnected.length() > 0) {
			std::wstring wid_str = std::wstring(sConnected.begin(), sConnected.end());
			const wchar_t* w_char = wid_str.c_str();

			Platform::String^ toChat = ref new Platform::String(w_char);
			if(toChat->Length() > 2)
			chatdata->Text += "Partner gefunden!\n";
		}

		UpdateChat();


		
		
	}
	else {
		chatdata->Text = "Pls select a place and a Activity.\n";
		
		
		
	}
	

}


void SC::MainPage::ort_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{

}


void SC::MainPage::aktivitaeten_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{

}


void SC::MainPage::button_Click_2(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	UpdateChat();
}
