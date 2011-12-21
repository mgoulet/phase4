/////////////////////////////////////////////////////////////////
//author: martin goulet
//SceneManager.cpp
/////////////////////////////////////////////////////////////////

#include "SceneManager.h"

/////////////////////////////////////////////////////////////////
//CONSTRUCTORS/DESTRUCTOR
/////////////////////////////////////////////////////////////////

SceneManager::SceneManager()
{
	//init
	this->Init();
}

SceneManager::~SceneManager()
{
	//release
	this->Release();
}

/////////////////////////////////////////////////////////////////
//METHODS
/////////////////////////////////////////////////////////////////

bool SceneManager::Init()
{
	unsigned long ul = this->timer.PollTimeInterval();
	ul = this->timer.PollTimeInterval();
	return true;
}

bool SceneManager::Release()
{
	return true;
}

bool SceneManager::RenderScene(const EntitySet& entityset_ref,
							   const ModelSet& modelset_ref,
							   const TextureSet& textureset_ref,
							   const SettingsSubSet& sss_ref) const
{
	//push matrix and attributes
	glPushMatrix();
	//push attribs
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	//load entity
	glLoadIdentity();
	//get proper camera reference
	CAM tempcam = entityset_ref.GetCAM();
	//perform camera transformation on modelview matrix
	gluLookAt( tempcam.vSVS[0].fCoords[0], tempcam.vSVS[0].fCoords[1],tempcam.vSVS[0].fCoords[2],
	tempcam.vSVS[1].fCoords[0]+tempcam.vSVS[0].fCoords[0], tempcam.vSVS[1].fCoords[1]+tempcam.vSVS[0].fCoords[1], tempcam.vSVS[1].fCoords[2]+tempcam.vSVS[0].fCoords[2],
	tempcam.vSVS[2].fCoords[0], tempcam.vSVS[2].fCoords[1], tempcam.vSVS[2].fCoords[2]);

	//render models if settings allow it
	if (sss_ref.GetKernelSettings().models3d)
	{
		this->RenderEntityModels(entityset_ref, modelset_ref);
	}

	//render math if settings allow it
	if (sss_ref.GetKernelSettings().math3d)
	{
		this->RenderEntityMath(entityset_ref);
	}

	//pop attribs
	glPopAttrib();
	//pop matrix
	glPopMatrix();
	
	//success
	return true;
}

bool SceneManager::RenderEntityModels(const EntitySet& entityset_ref, const ModelSet& modelset_ref) const
{
	//DISPLAY MODELS TO ALL ENTITIES
	for (int i = 0; i < entityset_ref.GetNumberOfEntities(); i++)
	{
		//get Hyper factor difference
		float fRelativeH = entityset_ref.GetCameraTargetRef()->fHVS[0]-
			entityset_ref.GetList().at(i)->fHVS[0];
		//adjusting 
		if (fRelativeH >= 340) {fRelativeH -= 360;}
		if (fRelativeH <= -340) {fRelativeH += 360;}

		//adjust it as a percentage of 20 degrees
		fRelativeH = abs(fRelativeH)/20;

		//render only if the entity is not followed by camera, and if 
		//hyper factor is in proper bounds.
		if ((entityset_ref.GetCameraTargetID() != i) &&
			(abs(fRelativeH) <= 20))
		{
			glPushMatrix();

			//set color & H factor
			glColor4f(1,1,1,1-(fRelativeH));

			//create a matrix for the current 
			VEC vx;
			MathManipulations::CroVEC(vx, entityset_ref.GetList().at(i)->vSVS[2], entityset_ref.GetList().at(i)->vSVS[1]);
			MathManipulations::NorVEC(vx);
			float matrix[16] = {
				vx.fCoords[0],
				vx.fCoords[1],
				vx.fCoords[2],
				0,
				entityset_ref.GetList().at(i)->vSVS[2].fCoords[0],
				entityset_ref.GetList().at(i)->vSVS[2].fCoords[1],
				entityset_ref.GetList().at(i)->vSVS[2].fCoords[2],
				0,
				entityset_ref.GetList().at(i)->vSVS[1].fCoords[0],
				entityset_ref.GetList().at(i)->vSVS[1].fCoords[1],
				entityset_ref.GetList().at(i)->vSVS[1].fCoords[2],
				0,
				entityset_ref.GetList().at(i)->vSVS[0].fCoords[0],
				entityset_ref.GetList().at(i)->vSVS[0].fCoords[1],
				entityset_ref.GetList().at(i)->vSVS[0].fCoords[2],
				1};

			//perform complete transformation
			glMultMatrixf(matrix);
			//render model of the current entity 'i' in entityset from loop increment
			//modelset_ref.GetModelList().at(entityset_ref.GetList().at(i)->GetModelType()).Render();
			//get a pointer to the model to be rendered.
			const CMD2Model* m_ptr = &modelset_ref.GetModelAt(entityset_ref.GetList().at(i)->iModel);
			//set animation stuff
			if (entityset_ref.GetList().at(i)->iType == 10) {m_ptr->Animate(0.01);m_ptr->SetAnimation(CMD2Model::RUN);}
			if (entityset_ref.GetList().at(i)->iType >= 20)	{m_ptr->Animate(1);m_ptr->SetAnimationCustom(1,1);}
			this->RenderMD2Frame(m_ptr);
			glPopMatrix();
		}
	}
	return true;
}

bool SceneManager::RenderMD2Frame(const CMD2Model* model_ptr) const
{
	//enable textures
	glEnable(GL_TEXTURE_2D);
	//enable depth test
	glEnable (GL_DEPTH_TEST);
	//enable face culling
	glEnable(GL_CULL_FACE);
	//use back face culling (quake2 style, some models...)
	glCullFace(GL_BACK);
	//render model
	model_ptr->Render();
	//disable face culing
	glDisable(GL_CULL_FACE);
	//disable depth test
	glDisable(GL_DEPTH_TEST);
	//disable textures
	glDisable(GL_TEXTURE_2D);

	//return success
	return true;
}

bool SceneManager::RenderEntityMath(const EntitySet& entityset_ref) const
{
	//init crap
	CAM c_ref = entityset_ref.GetCAM();
	EE* ee_ptr = entityset_ref.GetList().at(0);

	for (int i = 0; i < entityset_ref.GetNumberOfEntities(); i++)
	{
		//get reference to current entity to draw
		ee_ptr = entityset_ref.GetList().at(i);

		//DISPLAY VECTORS
		glLoadIdentity();
		glPushMatrix();
		gluLookAt( c_ref.vSVS[0].fCoords[0], c_ref.vSVS[0].fCoords[1],c_ref.vSVS[0].fCoords[2],
		c_ref.vSVS[1].fCoords[0]+c_ref.vSVS[0].fCoords[0], c_ref.vSVS[1].fCoords[1]+c_ref.vSVS[0].fCoords[1], c_ref.vSVS[1].fCoords[2]+c_ref.vSVS[0].fCoords[2],
		c_ref.vSVS[2].fCoords[0], c_ref.vSVS[2].fCoords[1], c_ref.vSVS[2].fCoords[2]);
			
		//translate position of entity
		glTranslatef(ee_ptr->vSVS[0].fCoords[0] - c_ref.vSVS[0].fCoords[0],
			ee_ptr->vSVS[0].fCoords[1] - c_ref.vSVS[0].fCoords[1],
			ee_ptr->vSVS[0].fCoords[2] - c_ref.vSVS[0].fCoords[2]);

		//try to draw lines of vectors
		VEC v1 = ee_ptr->vSVS[0]; //Pos
		VEC v2 = ee_ptr->vSVS[1]; //Dir
		VEC v3 = ee_ptr->vSVS[2]; //Nor
		VEC vCro;

		MathManipulations::NorVEC(v2);
		MathManipulations::NorVEC(v3);
		MathManipulations::CroVEC(vCro, v2, v3);
		MathManipulations::NorVEC(vCro);
		MathManipulations::MulVEC(vCro, 2);
		
		//CHECK FOR COLLISION
		if (entityset_ref.GetList().at(i)->bIsColliding)
		{
			glColor4f(1,0,0,1);
		}
		else
		{
			glColor4f(0,0,0,1);
		}

		if (i != entityset_ref.GetCameraTargetID())
		{
			glLineWidth(1);
			glBegin(GL_LINES);
				glVertex3f(v1.fCoords[0], v1.fCoords[1], v1.fCoords[2]);
				glVertex3f(v1.fCoords[0]+v2.fCoords[0]*10, v1.fCoords[1]+v2.fCoords[1]*10, v1.fCoords[2]+v2.fCoords[2]*10);
			glEnd();
			glBegin(GL_LINES);
				glVertex3f(v1.fCoords[0], v1.fCoords[1], v1.fCoords[2]);
				glVertex3f(v1.fCoords[0]+v3.fCoords[0]*5, v1.fCoords[1]+v3.fCoords[1]*5, v1.fCoords[2]+v3.fCoords[2]*5);
			glEnd();
			
			glBegin(GL_TRIANGLES);
				glVertex3f(v1.fCoords[0]+v2.fCoords[0]*5, v1.fCoords[1]+v2.fCoords[1]*5, v1.fCoords[2]+v2.fCoords[2]*5);
				glVertex3f(v1.fCoords[0]+vCro.fCoords[0],v1.fCoords[1]+vCro.fCoords[1], v1.fCoords[2]+vCro.fCoords[2]);
				glVertex3f(v1.fCoords[0]+(-1*vCro.fCoords[0]),v1.fCoords[1]+(-1*vCro.fCoords[1]), v1.fCoords[2]+(-1*vCro.fCoords[2]));
			glEnd();
		}
	}
	glPopMatrix();

	return true;
}




