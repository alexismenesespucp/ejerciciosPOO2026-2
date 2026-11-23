#pragma once

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;
using namespace JuegoModel;
using namespace JuegoPersistence;
using namespace System::Net;
using namespace System::Net::Sockets;

namespace JuegoController {
	public ref class Controller abstract sealed
	{
	public:
		static List<String^>^ ips;
		static List<String^>^ conexionesActivas;
		static tablero^ tableroActual;
		static void DibujarTablero(Graphics^ e);
		static void PintarCelda(int x, int y);
		static void  GuardarConexion(String^ IP) {
			Database::GuardarConexion(IP);
		}
		static void UpdateConexion(String^ IP) {
			Database::UpdateConexion(IP);
		}

		static void ObtenerIps() {
			if(ips != nullptr) {
				ips->Clear();
			} else {
				ips = gcnew List<String^>();
			}

			String^ hostName = Dns::GetHostName();
			IPHostEntry^ hostEntry = Dns::GetHostEntry(hostName);
			for each (IPAddress ^ ip in hostEntry->AddressList) {
				if (ip->AddressFamily == AddressFamily::InterNetwork) {
					String^ ipAddress = ip->ToString();
					ips->Add(ipAddress);
				}
			}
		}

		static List<String^>^ ObtenerConexionActivas() {
			return Database::ObtenerConexionActivas();
		}
		// TODO: Add your methods for this class here.
	};
}
