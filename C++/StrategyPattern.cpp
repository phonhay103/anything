#include <iostream>

class ShareStrategy
{
    public:
    virtual void share()
    {
        std::cout << "Sharing the photo" << std::endl;
    }
};

class PhoneCameraApp
{
    protected:
    ShareStrategy *shareStrategy;

    public:
    PhoneCameraApp(){}
    ~PhoneCameraApp()
    {
        delete shareStrategy;
    }

    void setShareStrategy(ShareStrategy *shareStrategy)
    {
        this->shareStrategy = shareStrategy;
    }
    
    void share()
    {
        shareStrategy->share();
    }

    void take()
    {
        std::cout << "Taking the photo" << std::endl;
    }

    void save()
    {
        std::cout << "Saving the photo" << std::endl;
    }

    virtual void edit()
    {
        std::cout << "Editing the photo" << std::endl;
    }
};

class Email : public ShareStrategy
{
	public:
    void share()
    {
		std::cout << "I'm emailing the photo" << std::endl;
	}
};

class Social : public ShareStrategy
{
    public:
    void share()
    {
        std::cout << "I'm posting the photo on social media" << std::endl;
    }
};

class Txt : public ShareStrategy
{
    public:
    void share()
    {
        std::cout << "I'm txting the photo" << std::endl;
    }
};

class BasicCameraApp : public PhoneCameraApp
{
	public:
    void edit()
    {
		std::cout << "Basic editing features" << std::endl;
	}
};

class CameraPlusApp : public PhoneCameraApp
{
    public:
    void edit()
    {
        std::cout << "Extra snazzy photo editing features" << std::endl;
    }
};

int main()
{
    PhoneCameraApp *P = new BasicCameraApp;
    P->setShareStrategy(new Social);
    P->take();
    P->edit();
    P->share();
    P->save();
    return 0;
}