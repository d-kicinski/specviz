import pytest


@pytest.fixture(scope='session', autouse=True)
def resources_directory(request):
    return str(request.config.rootdir) + "/tests/resources"
