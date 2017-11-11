#pragma once

#include <string>
#include <fstream>

#include "libconfig.h"

#include "..\Modules\IParameters.h"
#include "..\Modules\ModuleCore.h"

using namespace libconfig;

class SaveConfiguration
{
public:
  SaveConfiguration(Core::Parameters *params, std::string path)
  {
    _params = params;
    _path = path;
  }

  void operator()()
  {
    Setting &root = _config.getRoot();

    Core(root.add("core", Setting::Type::TypeGroup), _params);

    _config.writeFile(_path.c_str());
  }

  void Core(Setting &setting, Core::Parameters *parameters)
  {
    Capture(setting.add("capture", Setting::Type::TypeGroup), _params->GetCaptureParams());
    Record(setting.add("record", Setting::Type::TypeGroup), _params->GetRecordParams());
    Vision(setting.add("vision", Setting::Type::TypeGroup), _params->GetVisionParams());
    Control(setting.add("control", Setting::Type::TypeGroup), _params->GetControlParams());
    Display(setting.add("display", Setting::Type::TypeGroup), _params->GetDisplayParams());
  }

  void Capture(Setting &setting, Capture::Parameters *parameters)
  {
    BaseParams(setting, parameters);

  }

  void Record(Setting &setting, Record::Parameters *parameters)
  {
    BaseParams(setting, parameters);

  }

  void Vision(Setting &setting, Vision::Parameters *parameters)
  {
    BaseParams(setting, parameters);

    DepthObstacle(setting.add("depthobstacle", Setting::Type::TypeGroup), parameters->GetDepthObstacleParams());
    TrafficLight(setting.add("trafficlight", Setting::Type::TypeGroup), parameters->GetTrafficLightParams());
    StopSign(setting.add("stopsign", Setting::Type::TypeGroup), parameters->GetStopSignParams());
  }

  void Control(Setting &setting, Control::Parameters *parameters)
  {
    BaseParams(setting, parameters);

  }

  void Display(Setting &setting, Display::Parameters *parameters)
  {
    BaseParams(setting, parameters);

  }

  void DepthObstacle(Setting &setting, DetectDepthObstacle::Parameters *parameters)
  {
    BaseParams(setting, parameters);

  }

  void TrafficLight(Setting &setting, DetectTrafficLight::Parameters *parameters)
  {
    BaseParams(setting, parameters);

  }

  void StopSign(Setting &setting, DetectStopSign::Parameters *parameters)
  {
    BaseParams(setting, parameters);

  }

  void BaseParams(Setting &setting, IParameters *parameters)
  {
    setting.add("mode", Setting::Type::TypeInt) = _params->GetMode();
    setting.add("toggle", Setting::Type::TypeInt) = _params->GetToggle();
  }

private:
  Core::Parameters *_params;
  std::string _path;

  libconfig::Config _config;
};