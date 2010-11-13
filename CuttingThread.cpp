#include "CuttingThread.h"

#include "Plotter.h"

CuttingThread::CuttingThread(QObject *parent) :
    QThread(parent)
{
	_media = 300;
	_speed = 10;
	_pressure = 10;
	_trackenhancing = false;
	_regmark = false;
	_regsearch = false;
	_regwidth = 0.0;
	_reglength = 0.0;
}


void CuttingThread::setParams(QList<QPolygonF> cuts, double mediawidth, double mediaheight, int media,
                              int speed, int pressure, bool trackenhancing,
                              bool regmark, bool regsearch, float regwidth, float reglength)
{
	// TODO: Move all this into a structure.
	_cuts = cuts;
	_media = media;
	_speed = speed;
	_pressure = pressure;
	_trackenhancing = trackenhancing;
	_regmark = regmark;
	_regsearch = regsearch;
	_regwidth = regwidth;
	_reglength = reglength;
	_mediawidth = mediawidth;
	_mediaheight = mediaheight;
}


void CuttingThread::run()
{
	Error e = Cut(_cuts, _mediawidth, _mediaheight, _media, _speed, _pressure, _trackenhancing,
	              _regmark, _regsearch, _regwidth, _reglength);
	if (e)
		emit success();
	else
		emit error(e.message().c_str());
	exec();
}