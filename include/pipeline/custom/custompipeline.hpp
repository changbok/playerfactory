
/*
 * custompipeline.hpp
 *
 *  Created on: 2013. 4. 22.
 *
 */

#ifndef CUSTOMPIPELINE_HPP_
#define CUSTOMPIPELINE_HPP_

#include <pipeline/pipeline.hpp>
#include <pipeline/custom/custom_comm_types.hpp>

namespace mediapipeline
{

/* src element handle */
typedef struct
{
  GstElement *pSrcElement;
//  GstElement          *pHlsQueue;

  MEDIA_SRC_ELEM_IDX_T srcIdx;
//  MEDIA_CHANNEL_T ch; // add 20111025

  guint bufferMinByte;
  guint bufferMaxByte;
  guint prebufferByte;

} MEDIA_SRC_T;

typedef enum
{
  CONTENT_TYPE_UNKNOWN = 0x00,
  CONTENT_TYPE_VIDEO = 0x01,  // video mask
  CONTENT_TYPE_AUDIO = 0x02,  // audio mask
  CONTENT_TYPE_MULTI = 0x03,  // video + audio mask : do not change the value
} CUSTOM_CONTENT_TYPE_T;

typedef enum
{
  CUSTOM_BUFFER_FEED = 0,
  CUSTOM_BUFFER_LOW,
  CUSTOM_BUFFER_FULL,
  CUSTOM_BUFFER_LOCKED,
} CUSTOM_BUFFERING_STATE_T;

typedef struct
{
  gboolean bUsePreroll;
  gboolean bIsPreroll;
  guint32 bufferedSize;
  guint32 maxBufferSize;
} CUSTOM_PREROLL_STATE_T;

typedef struct
{
  guint8 contentType;
  gchar pElementName[15];
} CUSTOM_CONTAINER_TABLE_T;

class CustomPipeline:public Pipeline
{
  friend class CustomPlayer;

private:

  /*
      Gstreamer Element Handle
  */
  /* pipeline handle */
  GstElement * m_pstPipeline;

  /* element handle */

  /* src element */
  MEDIA_SRC_T m_stSrcInfo[IDX_MAX];

  /* demux element */
  GstElement *m_pstDemuxElement;

  /* video element */
  GstElement *pVideoQueueElement;
  GstElement *pVideoDecoderElement;

  /* audio element */
  GstElement *pAudioQueueElement;
  GstElement *pAudioDecoderElement;
  GstElement *pAudioSelectorElement;

  GstPad *pAudioSrcPad[MAX_TRACK_NUM];
  GstPad *pAudioSinkPad[MAX_TRACK_NUM];
  //GstPad *pVideoPad[MAX_TRACK_NUM]; // To Do (for TS)

  /* other element */
  GstElement *pRtpJitterBufferElement;
  GstElement *pDepayQueueElement;
  GstElement *pDepayElement;

  GstElement *pDrmElement;

  GstElement *pDownloadQueueElement;
  GstElement *pDownloadSinkElement;

  GstElement *pSubtitleSinkElement;

  /* local values */
  MEDIA_CUSTOM_CONTENT_INFO_T m_stContentInfo;
  CUSTOM_CONTENT_TYPE_T m_eContentType;
  MEDIA_CUSTOM_SRC_TYPE_T m_eSrcType;
  guint8 m_uNumOfSrc;
  gint m_CheckNum;
  CUSTOM_BUFFERING_STATE_T m_eNeedFeedData[IDX_MAX];
  CUSTOM_PREROLL_STATE_T m_stPrerollState;
  CUSTOM_CONTAINER_TABLE_T m_stDmxList[4];

  CustomPipeline ();

  guint8 _CheckContentType (void);
  void _callbackStopFeed (GstElement * element, MEDIA_SRC_T * app);
  gboolean _callbackSeekData (GstElement * element, guint64 offset,
                              MEDIA_SRC_T * app);
  void _callbackStartFeed (GstElement * element, guint32 size,
                           MEDIA_SRC_T * app);
  void _addNewPad (GstElement * element, GstPad * pad, gpointer data);

  MEDIA_STATUS_T _initValue (void);
  MEDIA_STATUS_T _addSrcElement (guint64 startOffset, const gchar * pSrcPath);
  MEDIA_STATUS_T _addSrcElement_Push (void);
  MEDIA_STATUS_T _addDemuxElement (void);
  void _findDemux (gchar ** pDemuxName);
  void _addVideoPad (GstPad * pad);
  MEDIA_STATUS_T _addVideoElement (void);
  MEDIA_STATUS_T _setPropertyOnVideo (void);
  void _addAudioPad (GstStructure * capsStr, GstPad * pad);
  void _addTextPad (GstPad * pad);

  static void playbinNotifySource (GObject * o, GParamSpec * p, gpointer d);
  static void handleVolumeChange (GObject * o, GParamSpec * p, gpointer d);
  static void handleMutedChange (GObject * o, GParamSpec * p, gpointer d);

public:
  ~CustomPipeline ();

  //void load();
  bool load (MEDIA_STREAMOPT_T * streamOpt, MEDIA_FORMAT_T mediaFormatType);
  bool load (MEDIA_CLIPOPT_T * clipOpt);
  MEDIA_STATUS_T load (MEDIA_CUSTOM_SRC_TYPE_T srcType,
                       const gchar * pSrcPath,
                       const gchar * pWritePath,
                       guint64 startOffset, MEDIA_CUSTOM_CONTENT_INFO_T * pstContentInfo);
  void unload ();
  bool play (int rate);
  gboolean informationMonitorStartSpi(guint32 timeInterval);
  gboolean positionSpi(gpointer data, gint64 *pos);

  MEDIA_STATUS_T FeedStream (guint8 * pBuffer, guint32 bufferSize,
                             guint64 pts, MEDIA_DATA_CHANNEL_T esData);

  GstElement getInstance () const;
  gint64 duration () const;
  gint64 position () const;
  gint volume () const;
  gboolean isMuted () const;
  gboolean isAudioAvailable () const;
  gboolean isVideoAvailable () const;
  gboolean isSeekable () const;
  gfloat playbackRate () const;

  //Error error() const;
  GString errorString () const;


};
}

#endif                          /* CUSTOMPIPELINE_HPP_ */


//end of file
