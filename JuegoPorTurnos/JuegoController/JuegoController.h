#pragma once

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;
using namespace JuegoModel;
using namespace JuegoPersistence;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Data;
using namespace System::IO;

namespace JuegoController {
	public ref class Controller abstract sealed
	{
	private:
		static PictureBox^ pbActualizacion;
	public:
		static void setPictureBox(PictureBox^ pb) {
			pbActualizacion = pb;
		}
		static List<String^>^ ips;
		static List<String^>^ conexionesActivas;
		static tablero^ tableroActual;
		static void DibujarTablero(Graphics^ e);
		static void PintarCelda(int x, int y);
		static void PintarCeldaOponente(int x, int y);
		static void  GuardarConexion(String^ IP) {
			Database::GuardarConexion(IP);
		}
		static void UpdateConexion(String^ IP) {
			Database::UpdateConexion(IP);
		}

		static void IniciarServidor() {
			int port = 5000;
			TcpListener^ listener = gcnew TcpListener(IPAddress::Any, port);
			try {
				listener->Start();
				Console::WriteLine("Servidor iniciado en el puerto " + port);
				while (true) {
					TcpClient^ client = listener->AcceptTcpClient();
					NetworkStream^ stream = client->GetStream();
					array<Byte>^ buffer = gcnew array<Byte>(1024);
					int bytesRead = stream->Read(buffer, 0, buffer->Length);
					if (bytesRead > 0) {
						String^ message = System::Text::Encoding::UTF8->GetString(buffer, 0, bytesRead);
						array<String^>^ parts = message->Split(',');
						int x = Convert::ToInt32(parts[0]);
						int y = Convert::ToInt32(parts[1]);
						Console::WriteLine("X,Y: " + x + "," + y);
						Controller::PintarCeldaOponente(x, y);
						pbActualizacion->Invalidate();
					}
					// Aquí puedes manejar la comunicación con el cliente
					client->Close();
				}

			}
			catch (Exception^ ex) {
				Console::WriteLine("Error al iniciar el servidor: " + ex->Message);
			}
			finally {
				listener->Stop();
			}

		}

		static void EnviarMensaje(String^ ip, String^ mensaje) {
			TcpClient^ cliente = nullptr;

			try {
				cliente = gcnew TcpClient(ip, 5000);
				NetworkStream^ stream = cliente->GetStream();
				StreamWriter^ writer = gcnew StreamWriter(stream);
				writer->WriteLine(mensaje);
				writer->Flush();
				Console::WriteLine("Mensaje enviado a " + ip + ": " + mensaje);

			}
			catch (Exception^ ex) {
				Console::WriteLine("Error al enviar mensaje a " + ip + ": " + ex->Message);
			}
			finally {
				if (cliente != nullptr) {
					cliente->Close();
				}
			}

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
