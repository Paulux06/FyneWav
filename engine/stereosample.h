#ifndef FYNEWAV_STEREOSAMPLE
#define FYNEWAV_STEREOSAMPLE
struct StereoSample
{
    double leftSample;
    double rightSample;
    StereoSample(double left, double right) {leftSample=left; rightSample=right;}
    StereoSample& operator+=(const StereoSample& strsmpl) {
        this->leftSample += strsmpl.leftSample;
        this->rightSample += strsmpl.rightSample;
        return *this;
    }
    StereoSample& operator+=(const double& mult) {
        this->leftSample += mult;
        this->rightSample += mult;
        return *this;
    }
    StereoSample& operator-=(const StereoSample& strsmpl) {
        this->leftSample -= strsmpl.leftSample;
        this->rightSample -= strsmpl.rightSample;
        return *this;
    }
    StereoSample& operator-=(const double& mult) {
        this->leftSample -= mult;
        this->rightSample -= mult;
        return *this;
    }
    StereoSample& operator*=(const StereoSample& strsmpl) {
        this->leftSample *= strsmpl.leftSample;
        this->rightSample *= strsmpl.rightSample;
        return *this;
    }
    StereoSample& operator*=(const double& mult) {
        this->leftSample *= mult;
        this->rightSample *= mult;
        return *this;
    }
    StereoSample& operator/=(const StereoSample& strsmpl) {
        this->leftSample /= strsmpl.leftSample;
        this->rightSample /= strsmpl.rightSample;
        return *this;
    }
    StereoSample& operator/=(const double& mult) {
        this->leftSample /= mult;
        this->rightSample /= mult;
        return *this;
    }
    StereoSample& operator*(const StereoSample& strsmpl) {
        StereoSample result(0, 0);
        result.leftSample = this->leftSample * strsmpl.leftSample;
        result.rightSample = this->rightSample * strsmpl.rightSample;
        return result;
    }
    StereoSample& operator*(const double& mult) {
        StereoSample result(0, 0);
        result.leftSample = this->leftSample * mult;
        result.rightSample = this->rightSample * mult;
        return result;
    }
    StereoSample& operator-(const StereoSample& strsmpl) {
        StereoSample result(0, 0);
        result.leftSample = this->leftSample - strsmpl.leftSample;
        result.rightSample = this->rightSample - strsmpl.rightSample;
        return result;
    }
    StereoSample& operator-(const double& mult) {
        StereoSample result(0, 0);
        result.leftSample = this->leftSample - mult;
        result.rightSample = this->rightSample - mult;
        return result;
    }
    StereoSample& operator+(const StereoSample& strsmpl) {
        StereoSample result(0, 0);
        result.leftSample = this->leftSample + strsmpl.leftSample;
        result.rightSample = this->rightSample + strsmpl.rightSample;
        return result;
    }
    StereoSample& operator+(const double& mult) {
        StereoSample result(0, 0);
        result.leftSample = this->leftSample + mult;
        result.rightSample = this->rightSample + mult;
        return result;
    }
    StereoSample& operator/(const StereoSample& strsmpl) {
        StereoSample result(0, 0);
        result.leftSample = this->leftSample / strsmpl.leftSample;
        result.rightSample = this->rightSample / strsmpl.rightSample;
        return result;
    }
    StereoSample& operator/(const double& mult) {
        StereoSample result(0, 0);
        result.leftSample = this->leftSample / mult;
        result.rightSample = this->rightSample / mult;
        return result;
    }
};
#endif