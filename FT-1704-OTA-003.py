#!/usr/bin/env python3
# -*-coding:utf-8-*-

import os
import re

import utils
import libMbctrl
import uavAdbControl
from exceptionLib import CaseFailException


image_path = os.path.join(os.getcwd(), 'data', 'eagle', 'Kernel')


def execute(s_thread, connection):
    # degrade
    uavAdbControl.deviceCmd('rm -rf /cache/ota.zip')
    uavAdbControl.pushFile(os.path.join('eagle', 'wm240', 'ota', 'ota.zip'), '/cache/ota.zip')
    uavAdbControl.deviceCmd('sync')
    s_thread.sendCmd('', 0)
    utils.sleep(2)
    s_thread.sendCmd('ota.sh', 0)
    utils.sleep(160)
    src_version = libMbctrl.mb_ctrl_version_1(s_thread, 8, 1)
    utils.log('src_version: %s' % src_version)

    fail_info = ''
    last_log = uavAdbControl.device_cmd_py3('ls /cache/recovery/last_log')
    if 'No such file' in str(last_log):
        fail_info = 'no file last_log found'
    else:
        ota_result = uavAdbControl.device_cmd_py3('cat /cache/recovery/last_log')
        if 'script succeeded' not in str(ota_result):
            fail_info = 'ota script failed'

    recovery_index = uavAdbControl.device_cmd_py3('cat /cache/update_recovery_index')
    re_index = re.search('(\d+)', str(recovery_index))
    index = 0
    if re_index:
        index = int(re_index.groups()[0])
        recovery_info = uavAdbControl.device_cmd_py3('cat /cache/update_recovery_log%s' % index)
        if 'failure' in str(recovery_info):
            fail_info += ', recovery verify failure'

    if fail_info:
        raise CaseFailException(fail_info, 'continue')

    # upgrade
    ota_folder = ''
    ota_name = ''
    for image in os.listdir(image_path):
        if image.find(s_thread.version_info) != -1:
            ota_folder = os.path.join(image_path, s_thread.version_info, 'image')
    for name in os.listdir(ota_folder):
        if name.find('full') != -1:
            ota_name = name
    if not ota_folder or not ota_name:
        raise CaseFailException('cannot find ota package')
    else:
        ota_path = os.path.join(ota_folder, ota_name)
    utils.log(ota_path)
    utils.log('s_thread version_info: %s' % s_thread.version_info)
    des_version = re.findall(r'.*v(\d{2}.\d{2}.\d{2}.\d{2}).*', s_thread.version_info)[0]
    utils.log('des version: %s' % des_version)
    uavAdbControl.deviceCmd('rm -rf /cache/ota.zip')
    uavAdbControl.pushFile2(ota_path, '/cache/ota.zip')
    uavAdbControl.deviceCmd('sync')
    s_thread.sendCmd('', 0)
    utils.sleep(2)
    s_thread.sendCmd('ota.sh', 0)
    utils.sleep(160)

    fail_info = ''
    last_log = uavAdbControl.device_cmd_py3('ls /cache/recovery/last_log')
    if 'No such file' in str(last_log):
        fail_info = 'no file last_log found'
    else:
        ota_result = uavAdbControl.device_cmd_py3('cat /cache/recovery/last_log')
        if 'script succeeded' not in str(ota_result):
            fail_info = 'ota script failed'

    recovery_index = uavAdbControl.device_cmd_py3('cat /cache/update_recovery_index')
    re_index = re.search('(\d+)', str(recovery_index))
    index = 0
    if re_index:
        index = int(re_index.groups()[0])
        recovery_info = uavAdbControl.device_cmd_py3('cat /cache/update_recovery_log%s' % index)
        if 'failure' in str(recovery_info):
            fail_info += ', recovery verify failure'

    if fail_info:
        raise CaseFailException(fail_info, 'continue')

    src_version = libMbctrl.mb_ctrl_version_1(s_thread, 8, 1)
    utils.log('src_version: {0}, des_version: {1}'.format(src_version, des_version))
    if src_version != des_version:
        raise CaseFailException('eagle version {0} is not expected version {1}'.format(src_version, des_version))