#include <VCSAPI.h>
#include <stdio.h>
#include <sys/time.h>    

//#define PRINT_GEO_INFO

long long getCurrentTime()    
{    
   struct timeval tv;    
   gettimeofday(&tv,NULL); 
   return tv.tv_sec * 1000 + tv.tv_usec / 1000;    
}

void TestDistPtPt3d()
{
	printf("begin TestDistPtPt3d\n");

	long long time_begin = getCurrentTime();

	VCSSystem* pVCS = VCSSystem::createVCSSystem(); //create VCS System
    
    VCSMPoint3d pt1(1, 0, 0);                       //create VCS geometries
    VCSMPoint3d pt2(2, 0, 0);
    
    VCSRigidBody* b1 = NULL;                        //create VCS bodies
    VCSRigidBody* b2 = NULL;
    VCSMPoint3d cor;
    VCSMMatrix3d t;
    pVCS->createRBody(b1, 1, t, cor);
    pVCS->createRBody(b2, 2, t, cor);
    b1->setGrounded(true);
    VCSConHandle* h = NULL;                         //create VCS constraints
    pVCS->create3dDistPtPt(h, b1, b2, pt1, pt2, NULL, NULL, 10, kVCSEQ);
    
    #ifdef PRINT_GEO_INFO
    VCSMPoint3d pt1R = pt1;                         //get solve result
    VCSMPoint3d pt2R = pt2;
    pt1R.transformBy(b1->transform());
    pt2R.transformBy(b2->transform());
    
    double x1 = pt1R.x;
    double y1 = pt1R.y;
    double x2 = pt2R.x;
    double y2 = pt2R.y;
    printf("before solve point1 x = %g y = %g \n", x1, y1);
    printf("before solve point2 x = %g y = %g \n", x2, y2);
    #endif
    
    VCSStatus status = pVCS->solve();               //solve VCS System
    
    #ifdef PRINT_GEO_INFO
    pt1R = pt1;                         //get solve result
    pt2R = pt2;
    pt1R.transformBy(b1->transform());
    pt2R.transformBy(b2->transform());
    
    x1 = pt1R.x;
    y1 = pt1R.y;
    x2 = pt2R.x;
    y2 = pt2R.y;
    printf("after solve point1 x = %g y = %g \n", x1, y1);
    printf("after solve point2 x = %g y = %g \n", x2, y2);
    #endif

    pVCS->free();                                   //free VCS System

	long long time_end = getCurrentTime();

	//printf("begin time is :%lld\n", time_begin);
	//printf("end time is :%lld\n", time_end);
	printf("cost time is :%lld\n", time_end-time_begin);

	printf("end TestDistPtPt3d\n\n");
}

void TestSymmPtPtPlTol()
{
	printf("begin TestSymmPtPtPlTol\n");

	long long time_begin = getCurrentTime();

	VCSSystem* pVCS = VCSSystem::createVCSSystem(); //create VCS System
    
    VCSMPoint3d pt1(1, 0, 0);                       //create VCS geometries
    VCSMPoint3d pt2(-1.05, 0, 0);
    VCSMPlane pl(VCSMPoint3d(0,0,0), VCSMVector3d(1,0,0));
    
    VCSRigidBody* b1 = NULL;                        //create VCS bodies
    VCSRigidBody* b2 = NULL;
    VCSRigidBody* b3 = NULL;
    VCSMPoint3d cor;
    VCSMMatrix3d t;
    pVCS->createRBody(b1, 1, t, cor);
    pVCS->createRBody(b2, 2, t, cor);
    pVCS->createRBody(b3, 3, t, cor);
    b1->setGrounded(true);
    double tol = 0.1;
    VCSConHandle* h = NULL;                         //create VCS constraints
    pVCS->create3dSymmPtPtPl(h, b1, b2, pt1, pt2, b3, pl, true, tol);
    
    #ifdef PRINT_GEO_INFO
    VCSMPoint3d pt1R = pt1;                         //get solve result
    VCSMPoint3d pt2R = pt2;
    pt1R.transformBy(b1->transform());
    pt2R.transformBy(b2->transform());
    
    double x1 = pt1R.x;
    double y1 = pt1R.y;
    double x2 = pt2R.x;
    double y2 = pt2R.y;
    printf("before solve point1 x = %g y = %g \n", x1, y1);
    printf("before solve point2 x = %g y = %g \n", x2, y2);
    #endif

    VCSStatus status = pVCS->solve();               //solve VCS System
    
    #ifdef PRINT_GEO_INFO
    pt1R = pt1;                         //get solve result
    pt2R = pt2;
    pt1R.transformBy(b1->transform());
    pt2R.transformBy(b2->transform());
    
    x1 = pt1R.x;
    y1 = pt1R.y;
    x2 = pt2R.x;
    y2 = pt2R.y;
    printf("before solve point1 x = %g y = %g \n", x1, y1);
    printf("before solve point2 x = %g y = %g \n", x2, y2);
    #endif

    pVCS->free();                                   //free VCS System

	long long time_end = getCurrentTime();

	printf("cost time is :%lld\n", time_end-time_begin);

	printf("end TestSymmPtPtPlTol\n\n");
}

void TestEllipse()
{
	printf("begin TestEllipse\n");

	long long time_begin = getCurrentTime();

	VCSSystem* pVCS = VCSSystem::createVCSSystem(); //create VCS System
	VCSEquationSystem* pEquationSys = VCSEquationSystem::createVCSEquationSystem();

	
	VCSRigidBody* b1 = NULL;                        //create VCS bodies
    VCSRigidBody* b2 = NULL;
    VCSRigidBody* b3 = NULL;
    VCSRigidBody* b4 = NULL;
    VCSRigidBody* b5 = NULL;
    VCSRigidBody* b6 = NULL;
    
    VCSMPoint3d cor;
    VCSMMatrix3d t;
    VCSRigidBody* b0 = NULL;
    pVCS->createRBody(b0, 999999, t, cor);
    b0->setGrounded(true);
    pVCS->createRBody(b1, 1, t, cor);
    b1->setGrounded(true);
    pVCS->createRBody(b2, 2, t, cor);
    pVCS->createRBody(b3, 3, t, cor);
    pVCS->createRBody(b4, 4, t, cor);
    pVCS->createRBody(b5, 5, t, cor);
    pVCS->createRBody(b6, 6, t, cor);

    //12
    VCSVarGeomHandle* varG6 = NULL;
    VCSConHandle* h = NULL;                         //create VCS constraints
    pVCS->create3dVariableEllipse(varG6, b6, VCSMEllipse3d(VCSMPoint3d(-200, 100, 0), VCSMVector3d(0, 0, 1), VCSMVector3d(1, 0, 0), 80, 60));

    //14
	VCSVarGeomHandle* varG7 = NULL;
    VCSRigidBody* b7 = NULL;
    pVCS->createRBody(b7, 7, t, cor);
    pVCS->create3dVariableEllipse(varG7, b7, VCSMEllipse3d(VCSMPoint3d(200, 100, 0), VCSMVector3d(0, 0, 1), VCSMVector3d(1, 0, 0), 80, 60));

    //16
    VCSVarGeomHandle* varG8 = NULL;
    VCSRigidBody* b8 = NULL;
    pVCS->createRBody(b8, 8, t, cor);
    pVCS->create3dVariableEllipse(varG8, b8, VCSMEllipse3d(VCSMPoint3d(-200, -100, 0), VCSMVector3d(0, 0, 1), VCSMVector3d(1, 0, 0), 80, 60));

    //18
    VCSVarGeomHandle* varG9 = NULL;
    VCSRigidBody* b9 = NULL;
    pVCS->createRBody(b9, 9, t, cor);
    pVCS->create3dVariableEllipse(varG9, b9, VCSMEllipse3d(VCSMPoint3d(200, -100, 0), VCSMVector3d(0, 0, 1), VCSMVector3d(1, 0, 0), 80, 60));

    VCSRigidBody* b10 = NULL;
    pVCS->createRBody(b10, 10, t, cor);

    VCSRigidBody* b11 = NULL;
    pVCS->createRBody(b11, 11, t, cor);

    //21
    pVCS->create3dDistPtPl(h, false, VCSMPoint3d(0, 0, 0), b2, b1, VCSMPoint3d(-200, 160, 0), VCSMPlane(VCSMPoint3d(0,0,0), VCSMVector3d(0,0,1)), NULL, NULL, 0, kVCSEQ, NULL);
	//22
	pVCS->create3dDistPtPl(h, false, VCSMPoint3d(0, 0, 0), b4, b1, VCSMPoint3d(-120, 100, 0), VCSMPlane(VCSMPoint3d(0,0,0), VCSMVector3d(0,0,1)), NULL, NULL, 0, kVCSEQ, NULL);
    //23
    pVCS->create3dDistPtPl(h, false, VCSMPoint3d(0, 0, 0), b5, b1, VCSMPoint3d(-200, 100, 0), VCSMPlane(VCSMPoint3d(0,0,0), VCSMVector3d(0,0,1)), NULL, NULL, 0, kVCSEQ, NULL);
    //24
    pVCS->create3dAngVecVec(h, false, VCSMPoint3d(0, 0, 0), VCSMPoint3d(0, 0, 0), b6, b1, VCSMVector3d(0, 0, 1), VCSMVector3d(0, 0, 1), NULL, NULL, kCodirectional, 0, kVCSEQ, NULL, VCSMVector3d(0, 0, 0), NULL, NULL, NULL);
    //25
    pVCS->create3dDistPtPl(h, false, VCSMPoint3d(0, 0, 0), b6, b1, VCSMPoint3d(-200, 160, 0), VCSMPlane(VCSMPoint3d(0,0,0), VCSMVector3d(0,0,1)), NULL, NULL, 0, kVCSEQ, NULL);
	//26
	pVCS->create3dMatePtEll(h, true, VCSMPoint3d(-200, 160, 0), b2, VCSMPoint3d(-200, 160, 0), varG6, true, NULL, NULL);
    //27
    pVCS->create3dMatePtEll(h, true, VCSMPoint3d(-200, 100, 0), b2, VCSMPoint3d(-200, 100, 0), varG6, true, NULL, NULL);
    //28
    pVCS->create3dDistPtPt(h, b6, b5, VCSMPoint3d(-200, 100, 0), VCSMPoint3d(-200, 100, 0), NULL, NULL, 0, kVCSEQ, NULL);
    //29
    pVCS->create3dAngVecVec(h, false, VCSMPoint3d(0, 0, 0), VCSMPoint3d(0, 0, 0), b10, b1, VCSMVector3d(0, 0, 1), VCSMVector3d(0, 0, 1), NULL, NULL, kCodirectional, 0, kVCSEQ, NULL, VCSMVector3d(0, 0, 0), NULL, NULL, NULL);
    //30
    pVCS->create3dDistPtPl(h, false, VCSMPoint3d(0, 0, 0), b10, b1, VCSMPoint3d(-200, 160, 0), VCSMPlane(VCSMPoint3d(0,0,0), VCSMVector3d(0,0,1)), NULL, NULL, 0, kVCSEQ, NULL);
	//31
	pVCS->create3dAngVecVec(h, false, VCSMPoint3d(0, 0, 0), VCSMPoint3d(0, 0, 0), b7, b1, VCSMVector3d(0, 0, 1), VCSMVector3d(0, 0, 1), NULL, NULL, kCodirectional, 0, kVCSEQ, NULL, VCSMVector3d(0, 0, 0), NULL, NULL, NULL);
    //32
    pVCS->create3dDistPtPl(h, false, VCSMPoint3d(0, 0, 0), b7, b1, VCSMPoint3d(-200, 160, 0), VCSMPlane(VCSMPoint3d(0,0,0), VCSMVector3d(0,0,1)), NULL, NULL, 0, kVCSEQ, NULL);
	//33
	pVCS->create3dTanLnEll(h, false, VCSMPoint3d(0, 0, 0), b10, VCSMLine3d(VCSMPoint3d(50, 50, 0), VCSMPoint3d(0.37139067635410372000000000000000, 0.92847669088525919000000000000000, 0)), varG7, NULL, NULL);
	//34
	pVCS->create3dAngVecVec(h, false, VCSMPoint3d(0, 0, 0), VCSMPoint3d(0, 0, 0), b7, b1, VCSMVector3d(0, 0, 1), VCSMVector3d(0, 0, 1), NULL, NULL, kCodirectional, 0, kVCSEQ, NULL, VCSMVector3d(0, 0, 0), NULL, NULL, NULL);
    //35
    pVCS->create3dDistPtPl(h, false, VCSMPoint3d(0, 0, 0), b11, b1, VCSMPoint3d(-200, 160, 0), VCSMPlane(VCSMPoint3d(0,0,0), VCSMVector3d(0,0,1)), NULL, NULL, 0, kVCSEQ, NULL);
	//36
	pVCS->create3dAngVecVec(h, false, VCSMPoint3d(0, 0, 0), VCSMPoint3d(0, 0, 0), b8, b1, VCSMVector3d(0, 0, 1), VCSMVector3d(0, 0, 1), NULL, NULL, kCodirectional, 0, kVCSEQ, NULL, VCSMVector3d(0, 0, 0), NULL, NULL, NULL);
    //37
    pVCS->create3dDistPtPl(h, false, VCSMPoint3d(0, 0, 0), b8, b1, VCSMPoint3d(-200, 160, 0), VCSMPlane(VCSMPoint3d(0,0,0), VCSMVector3d(0,0,1)), NULL, NULL, 0, kVCSEQ, NULL);
	//38
	pVCS->create3dAngVecVec(h, false, VCSMPoint3d(0, 0, 0), VCSMPoint3d(0, 0, 0), b9, b1, VCSMVector3d(0, 0, 1), VCSMVector3d(0, 0, 1), NULL, NULL, kCodirectional, 0, kVCSEQ, NULL, VCSMVector3d(0, 0, 0), NULL, NULL, NULL);
    //39
    pVCS->create3dDistPtPl(h, false, VCSMPoint3d(0, 0, 0), b9, b1, VCSMPoint3d(-200, 160, 0), VCSMPlane(VCSMPoint3d(0,0,0), VCSMVector3d(0,0,1)), NULL, NULL, 0, kVCSEQ, NULL);
	//40
	pVCS->create3dSymmEllEllLn(h, b11, VCSMLine3d(VCSMPoint3d(0, -200, 0), VCSMPoint3d(0, 1, 0)), varG8, varG9);
	//41
	b11->setGrounded(true);
	//42
	pVCS->create3dDistPtPl(h, false, VCSMPoint3d(0, 0, 0), b3, b1, VCSMPoint3d(-120, -100, 0), VCSMPlane(VCSMPoint3d(0,0,0), VCSMVector3d(0,0,1)), NULL, NULL, 0, kVCSEQ, NULL);
	//43
	pVCS->create3dMatePtEll(h, 0, VCSMPoint3d(-200, 160, 0), b3, VCSMPoint3d(-120, -100, 0), varG8, true, NULL, NULL);

    VCSStatus status = pVCS->solve();               //solve VCS System

    printf("solve result is :%d\n", status);

    pVCS->free();                                   //free VCS System

	long long time_end = getCurrentTime();

	//printf("begin time is :%lld\n", time_begin);
	//printf("end time is :%lld\n", time_end);
	printf("cost time is :%lld\n", time_end-time_begin);

	printf("end TestEllipse\n\n");
}

int main()
{
	TestDistPtPt3d();
	TestSymmPtPtPlTol();
	TestEllipse();
	return 0;
}