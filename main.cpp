#include <QCoreApplication>
#include <QSerialPort>
#include <QDebug>

QSerialPort qport;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qport.setPortName("/dev/ttyO4"); //MASTER comport  : /dev/ttyO4
    qport.setBaudRate(QSerialPort::Baud9600);
    qport.setDataBits(QSerialPort::Data8);
    qport.setParity(QSerialPort::NoParity);
    qport.setStopBits(QSerialPort::OneStop);
    qport.setFlowControl(QSerialPort::NoFlowControl);

    return a.exec();
}
void ReadDateTime(){

    bool serialport= qport.open(qport.ReadWrite);
    if(!serialport){
        qDebug()<<"Port3 error "<<qport.errorString();
    }
    QByteArray request,response;
    request.append("%RR#12340003E800003C**\r");
    qDebug()<<"Request "<<request;
    qport.clear();
    qDebug()<<" Open port "<<qport.write(request,request.size());
    do{
        while(!qport.bytesAvailable()){
             qDebug()<<"-KKC_CON_ERR";
        }
        response.append(qport.readAll());
        qDebug()<<"Responce : "<<response<<" size: "<<response.size();
    }while (response.size()<9);
    qport.close();
}
