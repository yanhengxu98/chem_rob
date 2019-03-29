# -*- coding: utf-8 -*-
import numpy as np
import scipy.optimize
import matplotlib.pyplot as plt


def import_data_txt(data_sheet):
    x = []
    y = []
    with open(data_sheet, 'r') as spectrum:
        for line in spectrum.readlines():
            if len(line.split()) == 2:
                wavelength = line.split()[0]
                power = line.split()[1]
                if float(wavelength) >= 400:
                    x.append(float(wavelength))
                    y.append(float(power))
            elif line.split():
                pass
            else:
                print("error reading")
                exit()
    return x, y


"""
* 创建系数矩阵X
* size - 2×size+1 = window_size
* rank - 拟合多项式阶次
* x - 创建的系数矩阵
"""


def create_x(size, rank):
    x = []
    for i in range(2 * size + 1):
        m = i - size
        row = [m**j for j in range(rank)]
        x.append(row)
    x = np.mat(x)
    return x


"""
 * Savitzky-Golay平滑滤波函数
 * data - list格式的1×n纬数据
 * window_size - 拟合的窗口大小
 * rank - 拟合多项式阶次
 * ndata - 修正后的值
"""


def savgol(data, window_size, rank):
    m = (window_size - 1) // 2
    odata = data[:]
    # 处理边缘数据，首尾增加m个首尾项
    for i in range(m):
        odata.insert(0, odata[0])
        odata.insert(len(odata), odata[len(odata)-1])
    # 创建X矩阵
    x = create_x(m, rank)
    # 计算加权系数矩阵B
    b = (x * (x.T * x).I) * x.T
    a0 = b[m]
    a0 = a0.T
    # 计算平滑修正后的值
    ndata = []
    for i in range(len(data)):
        y = [odata[i + j] for j in range(window_size)]
        y1 = np.mat(y) * a0
        y1 = float(y1)
        ndata.append(y1)
    return ndata


def find_peak_and_trough(x, y):
    peaks = []
    troughs = []
    for power in range(1, len(y) - 1):
        if 100 <= power <= len(y) - 101:
            count_peak = 0
            count_trough = 0
            for num in range(1, 100):
                if y[power - num] < y[power] > y[power + num]:
                    count_peak += 1
                else:
                    break
            for num in range(1, 100):
                if y[power - num] > y[power] < y[power + num]:
                    count_trough += 1
                else:
                    break
            if count_peak >= 90:
                peaks.append((power, y[power]))
                # print(x[power])
            if count_trough >= 90:
                troughs.append((power, y[power]))
                # print(x[power])
    return peaks, troughs


def calculate_half_wave_width(peaks, troughs, x, y_filtered):
    peak_largest = 0
    peak_second = 0
    x_peak = 0
    x_second = 0
    troughs_smallest = 10000
    x_trough = 0
    left_point_x, right_point_x, left_point_y, right_point_y = 0, 0, 0, 0

    for peak in peaks:
        if peak[1] > peak_largest:
            # peak_second = peak_largest
            peak_largest = peak[1]
            x_peak = peak[0]
            # x_second = x_peak
    for trough in troughs:
        if trough[1] < troughs_smallest:
            troughs_smallest = trough[1]
            x_trough = trough[0]
    half_wave_power = (peak_largest + troughs_smallest) / 2
    for sequence in range(x_trough, x_peak):
        if abs(y_filtered[sequence] - half_wave_power) <= 0.001:
            left_point_x = sequence
            left_point_y = y_filtered[sequence]
            break
    for sequence in range(x_peak, len(y_filtered)-100):
        if abs(y_filtered[sequence]) - half_wave_power <= 0.001:
            right_point_x = sequence
            right_point_y = y_filtered[sequence]
            break
    half_wave_width = x[right_point_x] - x[left_point_x]
    peak_intensity = peak_largest
    return x_peak, left_point_x, right_point_x, half_wave_width, peak_intensity


def _1gaussian(x, amp1, cen1, sigma1):
    return amp1*(1/(sigma1*(np.sqrt(2*np.pi))))*(np.exp(-((x-cen1)**2)/((2*sigma1)**2)))


def _2gaussian(x, amp1, cen1, sigma1, amp2, cen2, sigma2):
    return amp1*(1/(sigma1*(np.sqrt(2*np.pi))))*(np.exp(-((x-cen1)**2)/((2*sigma1)**2))) +\
           amp2*(1/(sigma2*(np.sqrt(2*np.pi))))*(np.exp(-((x-cen2)**2)/((2*sigma2)**2)))


def spectrum_analysis():
    x, y = import_data_txt("./spectrum/sample.txt")
    filtered_y = savgol(y, 9, 3)
    for i in range(0, 25):
        filtered_y = savgol(filtered_y, 9, 3)
    fig = plt.figure(figsize=(8, 6), dpi=300)
    plt.plot(x, filtered_y, color='r', label="spectrum")
    peaks, troughs = find_peak_and_trough(x, filtered_y)
    xpk, lpx, rpx, hww, pi = calculate_half_wave_width(peaks, troughs, x, filtered_y)
    fitting_x = x[(xpk + lpx) // 2:(rpx + xpk) // 2]
    fitting_y = filtered_y[(xpk + lpx) // 2:(rpx + xpk) // 2]
    print("The half wave width is %f nm. \nThe peak intensity is %f dB." % (hww, pi))
    plt.plot([x[lpx], x[rpx]], [filtered_y[lpx], filtered_y[lpx]], color='black',
             linewidth=2.5, linestyle='--', marker='.')
    plt.annotate("hww = %.3f" % (x[rpx] - x[lpx]), xy=((x[rpx] + x[lpx]) / 2, filtered_y[rpx]),
                 xytext=(-30, -20), textcoords='offset points')
    plt.annotate("(%.3f,%.3f)" % (x[xpk], pi), xy=(x[xpk], pi),
                 xytext=(+30, 0), textcoords='offset points',
                 arrowprops=dict(arrowstyle="->", connectionstyle="arc3,rad=.2"))
    popt_gauss, pcov_gauss = scipy.optimize.curve_fit(_1gaussian, fitting_x, fitting_y, p0=[90, 545, 60])
    print(popt_gauss)
    y2 = [_1gaussian(i, popt_gauss[0], popt_gauss[1], popt_gauss[2]) for i in x[2 * lpx - xpk: 3 * xpk - 2 * lpx]]
    plt.plot(x[2 * lpx - xpk: 3 * xpk - 2 * lpx], y2, color='blue', linestyle='--')
    plt.show()
    # perr_gauss = np.sqrt(np.diag(pcov_gauss))


# if __name__ == '__main__':
#     x, y = import_data_txt("./spectrum/sample.txt")
#     filtered_y = savgol(y, 9, 3)
#     for i in range(0, 25):
#         filtered_y = savgol(filtered_y, 9, 3)
#     fig = plt.figure(figsize=(8, 6), dpi=300)
#     # plt.scatter(x, y, color='r', marker='.')
#     plt.plot(x, filtered_y, color='r', label="spectrum")
#
#     peaks, troughs = find_peak_and_trough(x, filtered_y)
#     xpk, lpx, rpx, hww, pi = calculate_half_wave_width(peaks, troughs, x, filtered_y)
#     fitting_x = x[(xpk + lpx) // 2:(rpx + xpk) // 2]
#     fitting_y = filtered_y[(xpk + lpx) // 2:(rpx + xpk) // 2]
#     # for k in range(len(fitting_y)):
#     #     fitting_y[k] = fitting_y[k] - 0.48
#     print("The half wave width is %f nm. \nThe peak intensity is %f dB." % (hww, pi))
#     # plt.annotate("(%.3f,%.3f)" % (x[lpx], filtered_y[lpx]), xy=(x[lpx], filtered_y[lpx]),
#     #              xytext=(-100, 0), textcoords='offset points',
#     #              arrowprops=dict(arrowstyle="->", connectionstyle="arc3,rad=.2"))
#     # plt.annotate("(%.3f,%.3f)" % (x[rpx], filtered_y[rpx]), xy=(x[rpx], filtered_y[rpx]),
#     #              xytext=(+30, 0), textcoords='offset points',
#     #              arrowprops=dict(arrowstyle="->", connectionstyle="arc3,rad=.2"))
#     plt.plot([x[lpx], x[rpx]], [filtered_y[lpx], filtered_y[lpx]], color='black',
#              linewidth=2.5, linestyle='--', marker='.')
#     plt.annotate("hww = %.3f" % (x[rpx] - x[lpx]), xy=((x[rpx] + x[lpx]) / 2, filtered_y[rpx]),
#                  xytext=(-30, -20), textcoords='offset points')
#     plt.annotate("(%.3f,%.3f)" % (x[xpk], pi), xy=(x[xpk], pi),
#                  xytext=(+30, 0), textcoords='offset points',
#                  arrowprops=dict(arrowstyle="->", connectionstyle="arc3,rad=.2"))
#
#     popt_gauss, pcov_gauss = scipy.optimize.curve_fit(_1gaussian, fitting_x, fitting_y, p0=[90, 545, 60])
#     #
#     # popt_2gauss, pcov_2gauss = scipy.optimize.curve_fit(_2gaussian, fitting_x, fitting_y,
#     #                                                     p0=[100, 520, 100, 100, 570, 100])
#     print(popt_gauss)
#     y2 = [_1gaussian(i, popt_gauss[0], popt_gauss[1], popt_gauss[2]) for i in x[2 * lpx - xpk: 3 * xpk - 2 * lpx]]
#     # y3 = [_1gaussian(i, popt_2gauss[3], popt_2gauss[4], popt_2gauss[5]) for i in x]
#     plt.plot(x[2 * lpx - xpk: 3 * xpk - 2 * lpx], y2, color='blue', linestyle='--')
#     # plt.plot(x, y3, color='green', linestyle='--')
#     plt.show()
#     # plt.savefig("aaa.png")
#     perr_gauss = np.sqrt(np.diag(pcov_gauss))

