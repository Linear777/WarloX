#pragma once


class OgldevApp
{
protected:
	OgldevApp();

	void CalcFPS();

	void RenderFPS();

	float GetRunningTime();

protected:

private:
	long long m_frameTime;
	long long m_startTime;
	int m_frameCount;
	int m_fps;
};
