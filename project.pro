TEMPLATE = subdirs

# If you link to Qt staticly, you must configure the kit as follows.
# Go to:
# Kit -> Build -> Build Steps -> Additional parameters
# and add:
# CONFIG+=QT_STATIC_LINKING
# This is required because qwt must be linked the same way Qt is linked to

SUBDIRS = \
  qwt \
  app

qwt.subdir = 3dparty/qwt
app.file = TypingAnalysis.pro
app.depends = qwt
