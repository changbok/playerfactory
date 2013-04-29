/*
 * genericplayer.cpp
 *
 *  Created on: 2013. 4. 5.
 *      Author: jeongseok.kim
 */

#include <glibmm-utils/glibmm-utils.h>
#include <pipeline/generic/genericplayer.hpp>
#include <pipeline/generic/genericpipeline.hpp>

using namespace mediapipeline;

GenericPlayer::GenericPlayer ()
{
  LOG_FUNCTION_SCOPE_NORMAL_D ("GenericPlayer");
  Pipeline::bsp_t pipeline = getPipeline ();
  pipeline.reset (new GenericPipeline ());
  setPipeline (pipeline);       // save to abstractplayer.
}

GenericPlayer::~GenericPlayer ()
{
  LOG_FUNCTION_SCOPE_NORMAL_D ("GenericPlayer");
}

gboolean GenericPlayer::playSpi (int rate)
{
  LOG_FUNCTION_SCOPE_NORMAL_D ("GenericPlayer");
  LOG_D ("playing", "GenericPlayer");
  Pipeline::bsp_t pipeline = getPipeline ();
  pipeline->play (rate);
  return true;
}

gboolean GenericPlayer::pauseSpi ()
{
  LOG_FUNCTION_SCOPE_NORMAL_D ("GenericPlayer");
  LOG_D ("pause", "GenericPlayer");
  Pipeline::bsp_t pipeline = getPipeline ();
  return pipeline->pause ();
}

gboolean GenericPlayer::loadSpi (MEDIA_STREAMOPT_T * streamOpt)
{
  LOG_FUNCTION_SCOPE_NORMAL_D ("GenericPlayer");

  std::cout << "not supported API at genericPlayer. " << endl;
}

gboolean GenericPlayer::loadSpi (MEDIA_CLIPOPT_T * clipOpt)
{
  LOG_FUNCTION_SCOPE_NORMAL_D ("GenericPlayer");

  Pipeline::bsp_t pipeline = getPipeline ();
//      pipeline.reset(new GenericPipeline()); //moved to create time..
//      setPipeline(pipeline);

  pipeline->init ();            //create gst pipeline
  pipeline->load (clipOpt);
}

gboolean GenericPlayer::unloadSpi ()
{
  LOG_FUNCTION_SCOPE_NORMAL_D ("GenericPlayer");
  Pipeline::bsp_t pipeline = getPipeline ();
  pipeline->unload ();
}

gboolean GenericPlayer::isReadyToPlay ()
{
  LOG_FUNCTION_SCOPE_NORMAL_D ("GenericPlayer");
  Pipeline::bsp_t pipeline = getPipeline ();
  return pipeline->isReadyToPlay ();
}

Pipeline::State GenericPlayer::getPendingPipelineState ()
{
  LOG_FUNCTION_SCOPE_NORMAL_D ("GenericPlayer");
  Pipeline::bsp_t pipeline = getPipeline ();
  return pipeline->getPendingPipelineState ();
}


gboolean GenericPlayer::setPlaybackRateSpi (gfloat rate)
{
  LOG_FUNCTION_SCOPE_NORMAL_D ("GenericPlayer");
  Pipeline::bsp_t pipeline = getPipeline ();
  pipeline->setPlaybackRate (rate);
}


     gint64 GenericPlayer::durationSpi () const
     {
       LOG_FUNCTION_SCOPE_NORMAL_D ("GenericPlayer");
       //Pipeline::bsp_t pipeline = getPipeline();
       //return pipeline->duration();
     }

gint64
     GenericPlayer::positionSpi () const
     {
       LOG_FUNCTION_SCOPE_NORMAL_D ("GenericPlayer");
       //Pipeline::bsp_t pipeline = getPipeline();
       //return pipeline->position();
     }

gint
     GenericPlayer::volumeSpi () const
     {
       LOG_FUNCTION_SCOPE_NORMAL_D ("GenericPlayer");
       //Pipeline::bsp_t pipeline = getPipeline();
       //return pipeline->volume();
     }

gboolean
     GenericPlayer::isMutedSpi () const
     {
       LOG_FUNCTION_SCOPE_NORMAL_D ("GenericPlayer");
       //Pipeline::bsp_t pipeline = getPipeline();
       //return pipeline->isMuted();
     }

gboolean
     GenericPlayer::isAudioAvailableSpi () const
     {
       LOG_FUNCTION_SCOPE_NORMAL_D ("GenericPlayer");
       //Pipeline::bsp_t pipeline = getPipeline();
       //return pipeline->isAudioAvailable();
     }

gboolean
     GenericPlayer::isVideoAvailableSpi () const
     {
       LOG_FUNCTION_SCOPE_NORMAL_D ("GenericPlayer");
       //Pipeline::bsp_t pipeline = getPipeline();
       //return pipeline->isVideoAvailable();
     }

gboolean
     GenericPlayer::isSeekableSpi () const
     {
       LOG_FUNCTION_SCOPE_NORMAL_D ("GenericPlayer");
       //Pipeline::bsp_t pipeline = getPipeline();
       //return pipeline->isSeekable();
     }

gfloat
     GenericPlayer::playbackRateSpi () const
     {
       LOG_FUNCTION_SCOPE_NORMAL_D ("GenericPlayer");
       //Pipeline::bsp_t pipeline = getPipeline();
       //return pipeline->playbackRate();
     }


//Error error() const = 0;
GString
     GenericPlayer::errorStringSpi () const
     {
       LOG_FUNCTION_SCOPE_NORMAL_D ("GenericPlayer");
       //Pipeline::bsp_t pipeline = getPipeline();
       //return pipeline->errorString();
     }
