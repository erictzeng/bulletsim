#pragma once
#include "tracked_object.h"
#include "clouds/pcl_typedefs.h"
#include "visibility.h"
#include "plotting_tracking.h"

class SimplePhysicsTracker {
public:
  Environment::Ptr m_env;
  TrackedObject::Ptr m_obj;
  VisibilityInterface* m_visInt;
  Eigen::MatrixXf m_estPts;
  Eigen::MatrixXf m_obsPts;
  Eigen::MatrixXf m_stdev;
  Eigen::VectorXf m_prior_dist;
  Eigen::VectorXf m_outlier_dist; //m_obsPts - m_estPts for the fake node responsible for an outlier observation. same for all obsPts.
  Eigen::MatrixXf m_obsDebug;

  ColorCloudPtr m_obsCloud;

  PointCloudPlot::Ptr m_obsInlierPlot;
  PointCloudPlot::Ptr m_obsPlot;
  PointCloudPlot::Ptr m_obsTransPlot;
  PlotSpheres::Ptr m_estPlot;
  PlotSpheres::Ptr m_estTransPlot;
  PlotLines::Ptr m_corrPlot;
  PointCloudPlot::Ptr m_debugPlot;
  bool m_enableObsInlierPlot, m_enableObsPlot, m_enableObsTransPlot, m_enableEstPlot, m_enableEstTransPlot, m_enableCorrPlot, m_enableDebugPlot;
  bool m_applyEvidence;

  SimplePhysicsTracker(TrackedObject::Ptr, VisibilityInterface*, Environment::Ptr);
  void updateInput(ColorCloudPtr filteredCloud);
  void doIteration();
};