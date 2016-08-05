//
//  VCSWrapper
//  emsVCS
//

#include "VCSAPI.h"
#include "stdio.h"
#include <string>

extern "C" {

    VCSSystem* Wrapper_createVCSSystem()
    {
        return VCSSystem::createVCSSystem();
    }
    
    VCSMPoint3d* Wrapper_createVCSMPoint3d(double x, double y, double z)
    {
        VCSMPoint3d* pt = new VCSMPoint3d(x, y, z);
        return pt;
    }
    
    VCSMMatrix3d* Wrapper_createVCSMMatrix3d()
    {
        VCSMMatrix3d* matrix = new VCSMMatrix3d();
        return matrix;
    }

    VCSRigidBody* Wrapper_createRBody(VCSSystem* pVCS,
                                      int id,
                                      VCSMMatrix3d* pos,
                                      VCSMPoint3d* cor)
    {
        VCSRigidBody* body = NULL;
        pVCS->createRBody(body, id, *pos, *cor);
        return body;
    }
    
    void Wrapper_create3dDistPtPt(VCSSystem* pVCS,
                                  VCSRigidBody* b1,
                                  VCSRigidBody* b2,
                            const VCSMPoint3d* pt1,
                            const VCSMPoint3d* pt2,
                                  double dist
                                  )
    {
        VCSConHandle* h = NULL;
        pVCS->create3dDistPtPt(h, b1, b2, *pt1, *pt2, NULL, NULL, dist, kVCSEQ);
    }
    
    VCSStatus Wrapper_solve(VCSSystem* pVCS)
    {
        return pVCS->solve();
    }

    const char* Wrapper_showVCSStatus(VCSStatus status)
    {
        // general
             if(status == 0) return "kNull";
        else if(status == 1) return "kError";
        else if(status == 2) return "kFailed";
        else if(status == 3) return "kBadMatrix";
        else if(status == 4) return "kOK";
        else if(status == 5) return "kExternallySolved";
        else if(status == 6) return "kPartiallySolved";
        else if(status == 7) return "kFatallyInconsistent";
        else if(status == 8) return "kExternallyInterrupted";

        // solve and constraint status
        else if(status == 9) return "kSolved";
        else if(status == 10) return "kSolvedMakingAssumptions";
        else if(status == 11) return "kInconsistent";
        else if(status == 12) return "kSolvedWithoutDOFAndRedundancyAnalysis";
        else if(status == 13) return "kSolvedWithExternalVerificationFailure";
        else if(status == 14) return "kRedundant";
        else if(status == 15) return "kJointDOFLocked";

        // constraint only status
        else if(status == 16) return "kNotSolved";
        else if(status == 17) return "kRotationSolvedOnly";
        else if(status == 18) return "kTranslationSolvedOnly";
        else if(status == 19) return "kRotationRedundantOnly";
        else if(status == 20) return "kTranslationRedundantOnly";
        else if(status == 21) return "kSolvedButRotationRedundant";
        else if(status == 22) return "kSolvedButTranslationRedundant";
    }
    
    int Wrapper_showPointX(VCSMPoint3d* pt, VCSRigidBody* body)
    {
        VCSMPoint3d newpt = *pt;
        newpt.transformBy(body->transform());
        return newpt.x;
    }
    
    int Wrapper_showPointY(VCSMPoint3d* pt, VCSRigidBody* body)
    {
        VCSMPoint3d newpt = *pt;
        newpt.transformBy(body->transform());
        return newpt.y;
    }
    
}

