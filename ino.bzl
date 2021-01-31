ArduinoInfo = provider(
  fields = {
    'files': 'Files'
  }
)

def _arduino_aspect_impl(target, ctx):
  files = []
  if hasattr(ctx.rule.attr, 'srcs'):
    for src in ctx.rule.attr.srcs:
      for f in src.files.to_list():
        files.append(f)

  if hasattr(ctx.rule.attr, 'hdrs'):
    for src in ctx.rule.attr.hdrs:
      for f in src.files.to_list():
        files.append(f)

  child_deps = [dep[ArduinoInfo].files for dep in ctx.rule.attr.deps]
  return [ArduinoInfo(files = depset(files, transitive = child_deps))]

arduino_aspect = aspect(implementation = _arduino_aspect_impl,
    attr_aspects = ['deps'],
)

def _ino_impl(ctx):
  out_files = []

  src_files = depset(ctx.files.srcs, transitive = [d[ArduinoInfo].files for d in ctx.attr.deps])
  for src in src_files.to_list():
    dest = ctx.actions.declare_file('{}/{}'.format(ctx.label.name, src.basename))
    ctx.actions.run_shell(
      outputs = [dest],
      inputs = [src],
      command = 'cp {} {}'.format(src.path, dest.path)
    )
    out_files.append(dest)

  return [DefaultInfo(files = depset(out_files))]

ino = rule(
  implementation = _ino_impl,
  attrs = {
    "srcs": attr.label_list(allow_files=[".ino"]),
    "deps": attr.label_list(aspects = [arduino_aspect])
  }
)
