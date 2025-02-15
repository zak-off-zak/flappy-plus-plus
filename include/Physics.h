#ifndef PHYSICS
#define PHYSICS

struct Vector2D {
  float x;
  float y;
};

class Object {
public:
  Vector2D position;
  Vector2D velocity;
  Vector2D acceleration;
  float mass;

  Object(float x, float y, float mass);

  void set_position(float x, float y);
  void set_velocity(float x, float y);
  void set_acceleration(float x, float y);

  void apply_force(Vector2D force);

  Vector2D get_velocity(float time);
  Vector2D get_postion(float time);

protected:
private:
};

#endif // !PHYSICS
