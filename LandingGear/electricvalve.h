#ifndef ELECTRICVALVE_H
#define ELECTRICVALVE_H

class AbstractValve
{
public:
  enum STATUS{
    ON,
    OFF
  };
   AbstractValve();
   void open(){m_status = ON;}
   virtual void close(){m_status = OFF;}

   int GetStatus(){return m_status;}

  int m_status;

};


class OpenDoorVlave:public AbstractValve
{


public:
  OpenDoorVlave(){
   m_status = OFF;
  }


private:

};

class CloseDoorVlave:public AbstractValve
{


public:
  CloseDoorVlave(){  m_status = OFF;}

private:
};

class ExtendGearValve:public AbstractValve
{

public:
  ExtendGearValve(){  m_status = OFF;}

private:

};

class RetracteGearValve:public AbstractValve
{
public:
  RetracteGearValve(){  m_status = OFF;}
private:


};

//通用电动阀
class GeneralValve:public AbstractValve
{

public:
  GeneralValve();
  void close() override;


  OpenDoorVlave* Getopendoorval(){return m_odv;}
  CloseDoorVlave* Getclosedoorval(){return m_cdv;}
  ExtendGearValve* Getextendgearval(){return m_egv;}
  RetracteGearValve* Getretractegearval(){return m_rgv ;}

private:


  OpenDoorVlave* m_odv;
  CloseDoorVlave* m_cdv;
  ExtendGearValve* m_egv;
  RetracteGearValve* m_rgv;
};

#endif // ELECTRICVALVE_H
