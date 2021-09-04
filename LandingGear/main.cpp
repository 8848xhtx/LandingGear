#include "widget.h"
#include <QApplication>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DExtras/qt3dwindow.h>
#include <Qt3DExtras/QForwardRenderer>
#include <Qt3DRender/QCamera>
#include <Qt3DExtras/QTorusMesh>
#include <Qt3DExtras/QPhongMaterial>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QPointLight>
#include <Qt3DRender/qsceneloader.h>
#include <Qt3DExtras/QOrbitCameraController>
#include <Qt3DRender/QMesh>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

Qt3DCore::QEntity* createScene();

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Widget w;
  w.show();
  return a.exec();

//  Qt3DExtras::Qt3DWindow *view = new Qt3DExtras::Qt3DWindow;
//  //view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x000000)));

//  QWidget* containter = QWidget::createWindowContainer(view);
//  containter->setMinimumSize(QSize(800,400));
//  containter->setMaximumSize(QSize(800,400));


//  QWidget* widget = new QWidget;
//  QPushButton* btntest = new QPushButton(widget);

//  widget->setWindowTitle("3d model test");
//  QHBoxLayout* hLayout = new QHBoxLayout(widget);
//  QVBoxLayout* vLayout = new QVBoxLayout();
//  vLayout->setAlignment(Qt::AlignTop);
//  hLayout->addWidget(containter,100);
//  hLayout->addLayout(vLayout);
//  hLayout->addWidget(btntest);
//  widget->show();
//  widget->resize(1000,600);

//  Qt3DCore::QEntity* rootEntity = createScene();

//  Qt3DRender::QCamera* camera = view->camera();
//  camera->lens()->setPerspectiveProjection(60.0f, (float)view->width() / view->height(), 0.1f, 1000.0f);
//  camera->setPosition(QVector3D(0,0, 40));
//  camera->setViewCenter(QVector3D(0,0,0));

//  Qt3DExtras::QOrbitCameraController* cameraController = new Qt3DExtras::QOrbitCameraController(rootEntity);
//  cameraController->setCamera(camera);
//  cameraController->setLookSpeed(180.0f);
//  cameraController->setLinearSpeed(50.0f);


//  view->setRootEntity(rootEntity);


//  view->show();


}

Qt3DCore::QEntity* createScene()
{
  Qt3DCore::QEntity* entity = new Qt3DCore::QEntity;
  Qt3DExtras::QPhongMaterial* torusMaterial = new Qt3DExtras::QPhongMaterial(entity);//创建材质

  Qt3DExtras::QTorusMesh* torusMesh = new Qt3DExtras::QTorusMesh(entity);
  torusMesh->setRadius(10.0f);
  torusMesh->setMinorRadius(6.0f);
  torusMesh->setSlices(16);
  torusMesh->setRings(32);

  //加载外部模型




  Qt3DRender::QSceneLoader* loader = new Qt3DRender::QSceneLoader(entity);
  QObject::connect(loader, &Qt3DRender::QSceneLoader::statusChanged,
          entity, [](Qt3DRender::QSceneLoader::Status s) {qDebug() << s;});


  loader->setSource(QUrl("qrc:/new/prefix1/x-35_obj.obj"));


  //Qt3DCore::QEntity* my_obj = new Qt3DCore::QEntity(entity);
//  Qt3DRender::QMesh* mesh = new Qt3DRender::QMesh();
//  mesh->setSource(QUrl("qrc:/new/prefix1/x-35_obj.obj"));

//  Qt3DExtras::QPhongMaterial* test_ojbMaterial = new Qt3DExtras::QPhongMaterial();
//  Qt3DCore::QEntity* meshEntity = new Qt3DCore::QEntity(entity);
//  Qt3DCore::QTransform * Transform = new Qt3DCore::QTransform();
//  Transform->setScale(0.01f);//模型的缩放
//  Transform->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));

//  meshEntity->addComponent(loader);
//  meshEntity->addComponent(test_ojbMaterial);
//  meshEntity->addComponent(Transform);



  Qt3DCore::QTransform* torusTransform = new Qt3DCore::QTransform(entity);

  entity->addComponent(torusMesh);
  entity->addComponent(torusMaterial);
  entity->addComponent(torusTransform);
  //entity->addComponent(mesh);
  entity->addComponent(loader);

    Qt3DCore::QEntity* Lightentity = new Qt3DCore::QEntity(entity);
    Qt3DRender::QPointLight* pointLight = new Qt3DRender::QPointLight(Lightentity);
    Qt3DCore::QTransform* lightTransform = new Qt3DCore::QTransform(entity);
    lightTransform->setTranslation(QVector3D(0,0,30));

    Lightentity->addComponent(pointLight);
    Lightentity->addComponent(lightTransform);


  return entity;
}
