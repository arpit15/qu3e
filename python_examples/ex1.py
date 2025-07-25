import qu3e_ext as qu3e

scene = qu3e.Scene(1.0 / 60.0)

# add floor
body_def = qu3e.BodyDef()
body = scene.create_body(body_def)

box_def = qu3e.BoxDef()

localSpace = qu3e.Transform()
qu3e.q3Identity(localSpace)
box_def.Set(localSpace, qu3e.Vec3(50.0, 1.0, 50.0))
body.add_box(box_def)

for i in range(10):
    scene.step()

print("done")
