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

	
	if (ort && aktivitaeten->SelectedIndex >= 0) {
		
		bIsConnected = true;
		chatdata->Text = "Connected.\n";
		std::string httpString;


		std::vector<std::string> selectedName = {"Kino", "Essen", "Fahrradfahren", "Party", "Chillen" , "LAN-Party" , "Fußball" };


		switch (aktivitaeten->SelectedIndex) {
		case 0:
			chatdata->Text += "Kino";
		break;


		case 1:
			chatdata->Text += "Essen";
		break;


		case 2:
			chatdata->Text += "Fahrradfahren";
		break;


		case 3:
			chatdata->Text += "Party";
		break;


		case 4:
			chatdata->Text += "Chillen";

		break;


		case 5:
			chatdata->Text += "LAN-Party";
		break;
		case 6:
			chatdata->Text += "Fußball";
		break;
		case 7:
			chatdata->Text += "Tennis";
		break;
		case 8:
			chatdata->Text += "Volleyball";
		break;
		case 9:
			chatdata->Text += "Basketball";
			break;
		case 10:
			chatdata->Text += "Spazieren gehen";
		break;
		case 11:
			chatdata->Text += "Reiten";
		break;
		case 12:
			chatdata->Text += "Yoga";
		break;


		}
		 
		
		//MessageBoxA()
			//System::Windows::Networking::PushNotifications::CreatePushNotificationChannelForApplicationAsync(String)
	}
	else {
		chatdata->Text = "Could not connect.\n";
		
		
		
		
		
	}
	

}


void SC::MainPage::ort_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{

}


void SC::MainPage::aktivitaeten_SelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e)
{

}
