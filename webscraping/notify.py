import gi
gi.require_version('Notify', '0.7')
from gi.repository import GLib, Notify
import os
import time

Notify.init("Test App")



class App():
    def __init__(self):
        self.last_notification = None
        Notify.init('Test')
    
    def open_url(self, notification, action_name, data):
        url = data
        os.system(f"firefox {url}")
    
    def googleNotification(self):
        self.last_notification =  Notify.Notification.new('Google')
        self.last_notification.add_action('clicked', 'Open in Browser', self.open_url, "https://www.google.com/")
        self.last_notification.show()


app = App()
app.googleNotification()
GLib.MainLoop().run()