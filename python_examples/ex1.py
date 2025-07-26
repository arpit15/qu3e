from time import time
import qu3e_ext as qu3e

start_time = time()
scene = qu3e.Scene(1.0 / 60.0, qu3e.Vec3(0.0, -9.8, 0.0), 5)

# add floor
body_def = qu3e.BodyDef()
# new body
body = scene.create_body(body_def)

box_def = qu3e.BoxDef()
box_def.SetRestitution(0.0)

localSpace = qu3e.Transform()
qu3e.q3Identity(localSpace)
box_def.Set(localSpace, qu3e.Vec3(50.0, 1.0, 50.0))
# add box to body
body.add_box(box_def)

# add static box
box_def.Set(localSpace, qu3e.Vec3(3.0, 2.0, 1.0))
body_def.position.Set(0.0, 2.0, 0.0)
body = scene.create_body(body_def)
body.add_box(box_def)

# add dynamic box
body_def.body_type = qu3e.BodyType.Dynamic
body_def.position.Set(2.5, 5.0, 0.0)
body = scene.create_body(body_def)
body.add_box(box_def)

for i in range(1000):
    scene.step()

scene.dump("scene.txt")
end_time = time()
print(f"done in {end_time - start_time:.4f} seconds")
