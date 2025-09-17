#include <pangolin/pangolin.h>
#include <unistd.h>

#include <fstream>
#include <sophus/se3.hpp>

using namespace std;

string ground_truth_file = "../ground_truth.txt";
string estimated_file = "../estimated.txt";

typedef vector<Sophus::SE3d, Eigen::aligned_allocator<Sophus::SE3d>>
    TrajectoryType;

TrajectoryType ReadTrajectory(const string& path);

void DrawTrajectory(const TrajectoryType& ground_truth,
                    const TrajectoryType& estimated);

int main() {
  TrajectoryType ground_truth = ReadTrajectory(ground_truth_file);
  // cout << ground_truth[0].translation().transpose() << endl;
  // cout << ground_truth[0].so3().unit_quaternion() << endl;
  TrajectoryType estimated = ReadTrajectory(estimated_file);
  assert(!ground_truth.empty() && !estimated.empty());
  assert(ground_truth.size() == estimated.size());

  double rmse = 0;
  for (size_t i = 0; i < estimated.size(); ++i) {
    Sophus::SE3d p1 = estimated[i], p2 = ground_truth[i];
    // (p2^-1 * p1).log(): se3 from the difference between p1 and p2
    // error = sqrt(rho_x^2 + rho_y^2 + rho_z^2 + phi_x^2 + phi_y^2 + phi_z^2)
    double error = (p2.inverse() * p1).log().norm();
    rmse += error * error;
  }
  rmse = rmse / double(estimated.size());
  rmse = sqrt(rmse);
  cout << "RMSE = " << rmse << endl;

  DrawTrajectory(ground_truth, estimated);

  return 0;
}

TrajectoryType ReadTrajectory(const string& path) {
  ifstream fin(path);
  TrajectoryType trajectory;
  if (!fin) {
    cerr << "trajectory " << path << "not found." << endl;
    return trajectory;
  }

  while (!fin.eof()) {
    double time, tx, ty, tz, qx, qy, qz, qw;
    fin >> time >> tx >> ty >> tz >> qx >> qy >> qz >> qw;
    Sophus::SE3d p1(Eigen::Quaterniond(qw, qx, qy, qz),
                    Eigen::Vector3d(tx, ty, tz));
    trajectory.push_back(p1);
  }

  return trajectory;
}

void DrawTrajectory(const TrajectoryType& ground_truth,
                    const TrajectoryType& estimated) {
  pangolin::CreateWindowAndBind("Trajectory Viewer", 1024, 768);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  pangolin::OpenGlRenderState s_cam(
      pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
      pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0));

  pangolin::View& d_cam = pangolin::CreateDisplay()
                              .SetBounds(0.0, 1.0, pangolin::Attach::Pix(175),
                                         1.0, -1024.0f / 768.0f)
                              .SetHandler(new pangolin::Handler3D(s_cam));

  while (pangolin::ShouldQuit() == false) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    d_cam.Activate(s_cam);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glLineWidth(2);
    for (size_t i = 0; i < ground_truth.size() - 1; i++) {
      glColor3f(0.0f, 0.0f, 1.0f);  // blue for ground truth
      glBegin(GL_LINES);
      auto p1 = ground_truth[i], p2 = ground_truth[i + 1];
      glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
      glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
      glEnd();
    }

    for (size_t i = 0; i < estimated.size() - 1; i++) {
      glColor3f(1.0f, 0.0f, 0.0f);  // red for estimated
      glBegin(GL_LINES);
      auto p1 = estimated[i], p2 = estimated[i + 1];
      glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
      glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
      glEnd();
    }
    pangolin::FinishFrame();
    usleep(5000);
  }
}