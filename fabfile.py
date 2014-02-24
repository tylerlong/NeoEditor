from fabric.api import local


def coffee():
    """start coffeescript daemon to compile dynamically"""
    local('coffee --watch --output javascript/ --compile coffee/')
