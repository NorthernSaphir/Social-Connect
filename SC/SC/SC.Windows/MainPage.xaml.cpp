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


void SC::MainPage::Button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	
	if (chatbox11->Text && bIsConnected) {
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


void SC::MainPage::Button_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

	
	if (ort->SelectedIndex >= 0 && aktivitaeten->SelectedIndex >= 0) {
		
		bIsConnected = true;
		chatdata->Text = "";
		chatdata->Text += "Überlege immer, mit wen du dich triffst.\n";
		chatdata->Text += "\n";
		std::string httpString;
		

		std::vector<Platform::String^> selectedName = { "Kino", "Essen", "Fahrradfahren", "Party", "Chillen" , "LAN-Party" , "Fußball" , "Tennis" , "Volleyball" , "Basketball", "Spazieren gehen" , "Reiten" , "Yoga" };
		std::vector<Platform::String^> selectedPlace = {"Flensburg", "Kiel", "Lübeck" , "Kaltenkirchen" , "Norderstedt" , "Neumünster" , "Hamburg" , "Itzehoe" , "Quickborn" , "Westerland" , "Fehmarn" , "Schleswig" , "Husum" , "Sant Peter-Ording" , "Wacken" , "Rendsburg" };
		chatdata->Text += selectedName.at(aktivitaeten->SelectedIndex) + "\n";
		chatdata->Text += selectedPlace.at(ort->SelectedIndex) + "\n";
		char buffer[256];
		sprintf(buffer, "hwid=777&reset=1&town=%i&act=%i", ort->SelectedIndex, aktivitaeten->SelectedIndex);
		g_Winsock.InitWinsock();
		g_Winsock.Connect("sc.r4p1d.xyz");
		g_Winsock.SendHttpGet("http://sc.r4p1d.xyz/chat.php", buffer);

		
		
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
