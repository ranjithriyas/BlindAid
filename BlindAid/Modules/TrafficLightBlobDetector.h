#pragma once

#include "TrafficLightBase.h"

namespace Vision
{
  namespace TrafficLight
  {
    namespace BlobDetector
    {
      class BlobDetector : public Base
      {
      public:
        BlobDetector(IParameters *params, IData *input, IData *output);

      private:
        void Process();
        void MaskColors();
        void DetectBlobs();
        void ConfirmWithBox();

        cv::Mat _hsvChannels[3];
        cv::Mat _bgrChannels[3];
        cv::Mat &_h;
        cv::Mat &_s;
        cv::Mat &_v;
        cv::Mat &_r;
        cv::Mat &_g;
        cv::Mat &_b;
        cv::Mat _blobMask[3];
      };
    }
  }
}