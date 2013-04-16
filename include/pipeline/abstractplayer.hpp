/*
 * abstractplayer.hpp
 *
 *  Created on: 2013. 4. 5.
 *      Author: jeongseok.kim
 */

#ifndef ABSTRACTPLAYER_HPP_
#define ABSTRACTPLAYER_HPP_

#include <vector>
#include <pipeline/player.hpp>
#include <pipeline/event/playeventlistener.hpp>

namespace mediapipeline {

class AbstractPlayer: public Player {
private:
	std::vector<PlayEventListener::bsp_t> _listeners;
	Pipeline::bsp_t _pipeline;

protected:
	AbstractPlayer();
	~AbstractPlayer();

	void setPipeline(Pipeline::bsp_t pipeline);

public:
	void addEventListener(PlayEventListener::bsp_t listener);

	Pipeline::bsp_t getPipeline();

	//void load();
	void load(MEDIA_STREAMOPT_T *streamOpt, MEDIA_FORMAT_T mediaFormatType);
	void load(MEDIA_CLIPOPT_T *clipOpt);
	void unload();
	void play(int rate);

    gint64 duration() const;
    gint64 position() const;
    gint volume() const;
	gboolean isMuted() const;
	gboolean isAudioAvailable() const;
	gboolean isVideoAvailable() const;
	gboolean isSeekable() const;
	gfloat playbackRate() const;

	//Error error() const;
	GString errorString() const;

	Pipeline::State m_userInputState; /* user input control status */


public: // for derived players
	//virtual void loadSpi() = 0;
	virtual void loadSpi(MEDIA_STREAMOPT_T *streamOpt, MEDIA_FORMAT_T mediaFormatType)=0;
	virtual void loadSpi(MEDIA_CLIPOPT_T *clipOpt)=0;

	virtual void unloadSpi() = 0;
	virtual void playSpi(int rate) = 0;

    virtual gint64 durationSpi() const = 0;
    virtual gint64 positionSpi() const = 0;
    virtual gint volumeSpi() const = 0;
	virtual gboolean isMutedSpi() const = 0;
	virtual gboolean isAudioAvailableSpi() const = 0;
	virtual gboolean isVideoAvailableSpi() const = 0;
	virtual gboolean isSeekableSpi() const = 0;
	virtual gfloat playbackRateSpi() const = 0;

	//Error error() const = 0;
	virtual GString errorStringSpi() const = 0;

};
}

#endif /* ABSTRACTPLAYER_HPP_ */
