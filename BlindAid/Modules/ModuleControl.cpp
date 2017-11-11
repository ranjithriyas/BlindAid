#include "ModuleControl.h"

using namespace std;
using namespace cv;

Control::Control(IParameters *params, IData *input, IData *output) : ControlBase(params, input, output)
{
  static bool connected = _serial.Open(_params->GetSerialPort(), _params->GetBaudRate());

  while (!connected)
  {
    cout << "connection failed!\n";

    Sleep(1000);
    connected = _serial.Open(_params->GetSerialPort(), _params->GetBaudRate());
  }

  cout << "connection success!\n";
}

void Control::operator()()
{
  GenerateControlString();
  CommandArduino();
}

void Control::CommandArduino()
{
  int bytesToSend = 6;
  int bytesSent = 0;

  _receivedLength = _serial.ReadData(_receivedMessage, 256);

  if (_receivedLength > 0)
    cout << "Received(" << _receivedLength << " bytes): " << _receivedMessage << endl;
  else
    cout << "Received nothing.\n";

  bytesSent = _serial.SendData(_controlMessage.c_str(), _controlMessage.length());

  if (bytesSent > 0)
    cout << "Sent(" << bytesSent << " bytes): " << _controlMessage << endl;
}

void Control::GenerateControlString()
{
  _controlMessage = "<";

  for (int i = 0; i < 5; ++i)
    _controlMessage += CalculateVibrationValue(_input->GetDepthObstacleResults()->GetMinColIntensity(i));

  for (int i = 0; i < 2; ++i)
    _controlMessage += CalculateVibrationValue(0);

  _controlMessage += ">";
}