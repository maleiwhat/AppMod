#ifndef DetailSynthesis_H
#define DetailSynthesis_H

#include "BasicHeader.h"

#include <cv.h>
#include <memory>

class Model;
class MeshParameterization;
class SynthesisTool;
class Shape;
class ParaShape;
class CurveGuidedVectorField;
class GLActor;
class KevinVectorField;
namespace LG {
class PolygonMesh;
}

class DetailSynthesis
{
public:
  typedef std::shared_ptr<Model> ModelPtr;
  typedef std::shared_ptr<ParaShape> ParaShapePtr;
  typedef std::shared_ptr<SynthesisTool> SynToolPtr;

public:
  DetailSynthesis();
  ~DetailSynthesis();

  void testMeshPara(std::shared_ptr<Model> model);
  void computeDisplacementMap(std::shared_ptr<Model> model); //old one; useless
  void prepareFeatureMap(std::shared_ptr<Model> model);
  void prepareDetailMap(std::shared_ptr<Model> model);
  void applyDisplacementMap(STLVectori vertex_set, std::shared_ptr<Shape> cut_shape, std::shared_ptr<Model> model, cv::Mat disp_map, cv::Mat mask);
  void startDetailSynthesis(std::shared_ptr<Model> model);
  void computeVectorField(std::shared_ptr<Model> model);
  void getDrawableActors(std::vector<GLActor>& actors);
  void testShapePlane(std::shared_ptr<Model> model);
  void mergeSynthesis(ParaShape* para_shape, std::shared_ptr<Model> model);
  void patchSynthesis(std::shared_ptr<Model> model);

  // transfer
  void doTransfer(std::shared_ptr<Model> src_model, std::shared_ptr<Model> tar_model);
  void test(std::shared_ptr<Model> model);
  void doGeometryTransfer(std::shared_ptr<Model> src_model, std::shared_ptr<Model> tar_model, STLVectori& sampled_t_v = STLVectori(), STLVectorf& sampled_t_new_v = STLVectorf(), bool do_complete = false);
  void doGeometryComplete(std::shared_ptr<Model> src_model, std::shared_ptr<Model> tar_model);

  void prepareParaPatches(std::shared_ptr<Model> src_model, std::shared_ptr<Model> tar_model, std::vector<int>& tar_sampled_v_ids, std::vector<int>& src_v_ids);

private:
  void computeFeatureMap(ParaShape* para_shape, std::vector<std::vector<float> >& feature_list, std::set<int>& visible_faces);
  void computeDetailMap(ParaShape* para_shape, std::vector<cv::Mat>& detail_image, std::shared_ptr<Model> model, std::set<int>& visible_faces, cv::Mat& mask);
  void computeDisplacementMap(ParaShape* para_shape, VertexList& new_mesh_v, FaceList& new_mesh_f, std::shared_ptr<Model> model, std::set<int>& visible_faces, cv::Mat& uv_mask);

  void prepareLocalTransformCrsp(ParaShapePtr src_para, ParaShapePtr tar_para, ModelPtr src_model, ModelPtr tar_model, SynToolPtr syn_tool, const std::vector<int>& tar_sampled, std::vector<STLVectori>& src_v_ids);

private:
  std::shared_ptr<MeshParameterization> mesh_para;
  std::shared_ptr<SynthesisTool>        syn_tool;
  std::shared_ptr<CurveGuidedVectorField> curve_guided_vector_field;
  std::shared_ptr<KevinVectorField> kevin_vector_field;
  std::vector<GLActor> actors;
  int resolution;
  double normalize_max;
  std::vector<float> detail_min, detail_max;
  float displacement_min, displacement_max;
 
private:
  DetailSynthesis(const DetailSynthesis&);
  void operator = (const DetailSynthesis&);
};
#endif // !DetailSynthesis_H