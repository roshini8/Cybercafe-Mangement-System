-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Generation Time: Jun 30, 2023 at 12:29 AM
-- Server version: 10.4.25-MariaDB
-- PHP Version: 8.1.10

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `device_mgmt`
--

-- --------------------------------------------------------

--
-- Table structure for table `admin`
--

CREATE TABLE `admin` (
  `Admin_id` varchar(10) NOT NULL,
  `Admin_name` varchar(50) NOT NULL,
  `Admin_ic` varchar(12) NOT NULL,
  `Admin_pass` varchar(10) NOT NULL,
  `Admin_phone` varchar(12) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `admin`
--

INSERT INTO `admin` (`Admin_id`, `Admin_name`, `Admin_ic`, `Admin_pass`, `Admin_phone`) VALUES
('Roshini23', 'ROSHINI', '021008070592', 'Ros2308', '01133040274'),
('Syukor12', 'Syukor Bin Hassan', '001208100427', 'Syukor0812', '0112345678');

-- --------------------------------------------------------

--
-- Table structure for table `booking`
--

CREATE TABLE `booking` (
  `NO` int(11) NOT NULL,
  `Booking_id` varchar(10) NOT NULL,
  `Member_id` varchar(10) NOT NULL,
  `Device_id` varchar(10) NOT NULL,
  `Booking_date` date NOT NULL,
  `Start_time` time NOT NULL,
  `End_time` time NOT NULL,
  `Duration` varchar(255) NOT NULL,
  `start_time_stamp` varchar(10) NOT NULL,
  `end_time_stamp` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `booking`
--

INSERT INTO `booking` (`NO`, `Booking_id`, `Member_id`, `Device_id`, `Booking_date`, `Start_time`, `End_time`, `Duration`, `start_time_stamp`, `end_time_stamp`) VALUES
(100, 'B0100', 'Rashmika', 'PC001', '2023-06-26', '19:00:00', '20:00:00', '1', 't11', 't12'),
(101, 'B0101', 'Darcy02', 'PC008', '2023-06-27', '09:00:00', '10:00:00', '1', 't1', 't2'),
(102, 'B0102', 'Darcy02', 'PC011', '2023-06-27', '10:00:00', '11:00:00', '1', 't2', 't3'),
(103, 'B0103', 'hafeizah', 'PC003', '2023-06-27', '09:00:00', '10:00:00', '1', 't1', 't2'),
(104, 'B0104', 'hafeizah', 'PT001', '2023-06-27', '09:00:00', '10:00:00', '1', 't1', 't2'),
(105, 'B0105', 'Mel', 'PC001', '2023-06-27', '09:00:00', '11:00:00', '2', 't1', 't3'),
(106, 'B0106', 'hafeizah', 'PC002', '2023-06-27', '09:00:00', '10:00:00', '1', 't1', 't2'),
(108, 'B0108', 'MICHEL12', 'PC001', '2023-06-27', '10:00:00', '11:00:00', '1', 't2', 't3'),
(109, 'B0109', 'Darrick02', 'PC002', '2023-06-27', '20:00:00', '21:00:00', '1', 't12', 't13'),
(110, 'B0110', 'Nancy08', 'PC008', '2023-06-27', '12:00:00', '13:00:00', '1', 't4', 't5'),
(111, 'B0111', 'Nancy08', 'PC001', '2023-06-27', '16:00:00', '17:00:00', '1', 't8', 't9'),
(65, 'B065', 'herish23', 'PC001', '2023-02-23', '17:00:00', '18:00:00', '1', 't9', 't10'),
(66, 'B066', 'herish23', 'PC001', '2023-04-08', '09:00:00', '10:00:00', '1', 't1', 't2'),
(67, 'B067', 'herish23', 'PC003', '2023-04-13', '18:00:00', '20:00:00', '2', 't10', 't12'),
(68, 'B068', 'herish23', 'PC003', '2023-04-14', '09:00:00', '10:00:00', '1', 't1', 't2'),
(69, 'B069', 'herish23', 'PC003', '2023-05-03', '18:00:00', '20:00:00', '2', 't10', 't12'),
(70, 'B070', 'herish23', 'PC002', '2023-05-03', '18:00:00', '19:00:00', '1', 't10', 't11'),
(71, 'B071', 'herish23', 'PC001', '2023-05-03', '18:00:00', '19:00:00', '1', 't10', 't11'),
(72, 'B072', 'herish23', 'PS001', '2023-05-03', '18:00:00', '19:00:00', '1', 't10', 't11'),
(73, 'B073', 'herish23', 'PS001', '2023-05-03', '19:00:00', '20:00:00', '1', 't11', 't12'),
(74, 'B074', 'herish23', 'PT001', '2023-05-03', '18:00:00', '19:00:00', '1', 't10', 't11'),
(75, 'B075', 'herish23', 'PT001', '2023-05-03', '19:00:00', '20:00:00', '1', 't11', 't12'),
(76, 'B076', 'herish23', 'PC001', '2023-05-03', '14:00:00', '15:00:00', '1', 't6', 't7'),
(77, 'B077', 'herish23', 'PC001', '2023-05-03', '19:00:00', '20:00:00', '1', 't11', 't12'),
(78, 'B078', 'herish23', 'PC002', '2023-05-03', '19:00:00', '20:00:00', '1', 't11', 't12'),
(79, 'B079', 'herish23', 'PC001', '2023-05-03', '15:00:00', '16:00:00', '1', 't7', 't8'),
(80, 'B080', 'herish23', 'PT001', '2023-05-03', '17:00:00', '18:00:00', '1', 't9', 't10'),
(81, 'B081', 'herish23', 'PS001', '2023-05-03', '20:00:00', '21:00:00', '1', 't12', 't13'),
(82, 'B082', 'herish23', 'PC001', '2023-05-03', '20:00:00', '21:00:00', '1', 't12', 't13'),
(83, 'B083', 'herish23', 'PC001', '2023-05-04', '09:00:00', '10:00:00', '1', 't1', 't2'),
(84, 'B084', 'herish23', 'PC002', '2023-05-15', '18:00:00', '20:00:00', '2', 't10', 't12'),
(85, 'B085', 'herish23', 'PC002', '2023-05-15', '19:00:00', '20:00:00', '1', 't11', 't12'),
(86, 'B086', 'herish23', 'PC003', '2023-05-15', '09:00:00', '11:00:00', '2', 't1', 't3'),
(87, 'B087', 'herish23', 'PS001', '2023-05-15', '09:00:00', '10:00:00', '1', 't1', 't2'),
(88, 'B088', 'herish23', 'PS001', '2023-05-15', '09:00:00', '10:00:00', '1', 't1', 't2'),
(89, 'B089', 'wahidah12', 'PC001', '2023-05-16', '09:00:00', '10:00:00', '1', 't1', 't2'),
(90, 'B090', 'herish23', 'PC001', '2023-05-15', '18:00:00', '19:00:00', '1', 't10', 't11'),
(91, 'B091', 'Nancy08', 'PC002', '2023-05-23', '09:00:00', '10:00:00', '1', 't1', 't2'),
(92, 'B092', 'Nancy08', 'PC001', '2023-05-31', '09:00:00', '11:00:00', '2', 't1', 't3'),
(93, 'B093', 'Nancy08', 'PC003', '2023-06-01', '11:00:00', '12:00:00', '1', 't3', 't4'),
(94, 'B094', 'Nancy08', 'PC002', '2023-06-01', '09:00:00', '10:00:00', '1', 't1', 't2'),
(95, 'B095', 'Nancy08', 'PT001', '2023-05-31', '09:00:00', '10:00:00', '1', 't1', 't2'),
(96, 'B096', 'Nancy08', 'PT001', '2023-05-31', '16:00:00', '17:00:00', '1', 't8', 't9'),
(97, 'B097', 'herish23', 'PC001', '2023-06-04', '09:00:00', '10:00:00', '1', 't1', 't2'),
(98, 'B098', 'wahidah12', 'PC001', '2023-06-07', '09:00:00', '10:00:00', '1', 't1', 't2'),
(99, 'B099', 'Nancy08', 'PC001', '2023-06-18', '09:00:00', '10:00:00', '1', 't1', 't2');

-- --------------------------------------------------------

--
-- Table structure for table `device`
--

CREATE TABLE `device` (
  `Device_id` varchar(10) NOT NULL,
  `Device_name` varchar(20) NOT NULL,
  `Device_Status` varchar(12) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `device`
--

INSERT INTO `device` (`Device_id`, `Device_name`, `Device_Status`) VALUES
('PC001', 'DELL', 'AVAILABLE'),
('PC002', 'HP DESKTOP', 'AVAILABLE'),
('PC003', 'LENOVO', 'AVAILABLE'),
('PC004', 'MSI Infinite', 'AVAILABLE'),
('PC005', 'HP ProDesk', 'AVAILABLE'),
('PC006', 'Intel NUC', 'AVAILABLE'),
('PC007', 'Razer Blade', 'AVAILABLE'),
('PC008', 'Apple iMac', 'AVAILABLE'),
('PC009', 'HP ProDesk', 'AVAILABLE'),
('PC010', 'Dell OptiPlex', 'AVAILABLE'),
('PC011', 'Acer Aspire', 'AVAILABLE'),
('PC012', 'Cosair One', 'AVAILABLE'),
('PC013', 'HP Pavilion', 'AVAILABLE'),
('PC014', 'MSI GF65 Thin', 'AVAILABLE'),
('PS001', 'PlayStation 5', 'AVAILABLE'),
('PS002', 'Playstation 3', 'AVAILABLE'),
('PS003', 'PlayStation 4 Pro', 'AVAILABLE'),
('PS004', 'PlayStation 4 Slim', 'AVAILABLE'),
('PT001', 'iMac 24-inch', 'AVAILABLE'),
('PT002', 'Lenovo Tab P11 Pro', 'AVAILABLE');

-- --------------------------------------------------------

--
-- Table structure for table `invoice`
--

CREATE TABLE `invoice` (
  `Invoice_Number` int(11) NOT NULL,
  `Payment_id` varchar(10) NOT NULL,
  `Invoice_date` date NOT NULL,
  `Invoice_time` time NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `invoice`
--

INSERT INTO `invoice` (`Invoice_Number`, `Payment_id`, `Invoice_date`, `Invoice_time`) VALUES
(22, 'P044', '2023-03-15', '01:44:29'),
(23, 'P045', '2023-04-08', '01:26:15'),
(24, 'P046', '2023-04-13', '15:56:32'),
(25, 'P047', '2023-04-13', '15:56:32'),
(26, 'P048', '2023-05-03', '11:28:59'),
(27, 'P049', '2023-05-03', '11:28:59'),
(28, 'P050', '2023-05-03', '12:11:10'),
(29, 'P051', '2023-05-03', '12:13:57'),
(30, 'P052', '2023-05-03', '12:13:57'),
(31, 'P053', '2023-05-03', '13:04:08'),
(32, 'P054', '2023-05-03', '13:24:46'),
(33, 'P055', '2023-05-03', '13:30:47'),
(34, 'P056', '2023-05-03', '13:35:53'),
(35, 'P057', '2023-05-03', '14:07:24'),
(36, 'P058', '2023-05-03', '14:09:11'),
(37, 'P059', '2023-05-03', '14:10:56'),
(38, 'P060', '2023-05-03', '14:15:49'),
(39, 'P062', '2023-05-04', '05:27:31'),
(40, 'P063', '2023-05-15', '10:37:22'),
(41, 'P064', '2023-05-15', '10:37:22'),
(42, 'P065', '2023-05-15', '10:40:25'),
(43, 'P066', '2023-05-15', '10:48:23'),
(44, 'P067', '2023-05-15', '10:51:22'),
(45, 'P068', '2023-05-15', '11:01:48'),
(46, 'P069', '2023-05-15', '11:11:06'),
(47, 'P070', '2023-05-23', '03:50:50'),
(48, 'P071', '2023-05-31', '06:15:20'),
(49, 'P072', '2023-05-31', '06:21:14'),
(50, 'P073', '2023-05-31', '06:21:14'),
(51, 'P074', '2023-05-31', '15:03:48'),
(52, 'P074', '2023-05-31', '15:03:48'),
(53, 'P076', '2023-06-04', '02:30:33'),
(54, 'P077', '2023-06-07', '06:26:28'),
(55, 'P078', '2023-06-17', '02:49:12'),
(56, 'P080', '2023-06-26', '18:02:56'),
(57, 'P081', '2023-06-27', '00:15:17'),
(58, 'P082', '2023-06-27', '00:52:08'),
(59, 'P083', '2023-06-27', '01:01:59'),
(60, 'P084', '2023-06-27', '01:01:59'),
(61, 'P085', '2023-06-27', '01:54:27'),
(62, 'P086', '2023-06-27', '01:54:27'),
(64, 'P088', '2023-06-27', '03:53:00'),
(65, 'P089', '2023-06-27', '07:29:53'),
(66, 'P091', '2023-06-27', '11:05:33'),
(67, 'P092', '2023-06-27', '11:05:33');

-- --------------------------------------------------------

--
-- Table structure for table `member`
--

CREATE TABLE `member` (
  `Member_id` varchar(10) NOT NULL,
  `Member_name` varchar(50) NOT NULL,
  `Member_ic` varchar(12) NOT NULL,
  `Member_pass` varchar(10) NOT NULL,
  `Member_phone` varchar(12) NOT NULL,
  `Member_start` date NOT NULL,
  `Member_end` date NOT NULL,
  `Member_points` int(11) NOT NULL,
  `Member_type` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `member`
--

INSERT INTO `member` (`Member_id`, `Member_name`, `Member_ic`, `Member_pass`, `Member_phone`, `Member_start`, `Member_end`, `Member_points`, `Member_type`) VALUES
('Aina05', 'Aina Binti Aziz', '980511135277', 'Aina0511', '0125792409', '2023-05-31', '2025-06-27', 0, 'BASIC'),
('Azalia', 'Siti Azalia', '020803070872', 'Azalia08', '01112475742', '2023-06-20', '2025-06-27', 0, 'STUDENT'),
('Darcy02', 'Darcy', '021003070594', 'Darcy0210', '0112376859', '2023-06-27', '2025-06-27', 40, 'BASIC'),
('Darrick02', 'Darrick', '021345070810', 'Darrick021', '0134789032', '2023-06-27', '2025-06-27', 20, 'BASIC'),
('hafeizah', 'Hafeizah', '021345060919', 'Hafeizah02', '0112475798', '2023-06-27', '2025-06-27', 60, 'BASIC'),
('herish23', 'Herish Chaudray', '021223100803', 'Roshini08', '0106680274', '2023-02-22', '2025-06-27', 1060, 'PREMIUM'),
('Mel', 'Melissa', '021223450945', 'Mel0212', '0112579834', '2023-06-27', '2025-06-27', 20, 'BASIC'),
('MICHEL12', 'MICHEL', '031224056704', 'Michel1203', '0164890467', '2023-06-27', '2025-06-27', 40, 'BASIC'),
('Nancy08', 'Nancy Thomas', '990807031003', 'Nancy0807', '0121255591', '2023-03-23', '2025-06-27', 140, 'PREMIUM'),
('Rashmika', 'Rashmika', '021003080274', 'Rashmika03', '0113759901', '2023-06-26', '2025-06-27', 20, 'BASIC'),
('wahidah12', 'Wahidah Binti Kamaruddin', '122345072314', 'Wahidah23', '0182312453', '2023-05-15', '2025-06-27', 40, 'BASIC'),
('yoges0711', 'Yogesvari', '710707075556', 'Yoges5556', '01115834057', '2023-03-10', '2025-06-27', 40, 'BASIC');

-- --------------------------------------------------------

--
-- Table structure for table `payment`
--

CREATE TABLE `payment` (
  `No` int(11) NOT NULL,
  `Payment_id` varchar(10) NOT NULL,
  `Booking_id` varchar(10) DEFAULT NULL,
  `Price` float NOT NULL,
  `Payment_date` date NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `payment`
--

INSERT INTO `payment` (`No`, `Payment_id`, `Booking_id`, `Price`, `Payment_date`) VALUES
(44, 'P044', 'B065', 3.5, '2023-03-15'),
(45, 'P045', 'B066', 3.5, '2023-04-08'),
(46, 'P046', 'B067', 7, '2023-04-13'),
(47, 'P047', 'B068', 3.5, '2023-04-13'),
(48, 'P048', 'B069', 7, '2023-05-03'),
(49, 'P049', 'B070', 3.5, '2023-05-03'),
(50, 'P050', 'B071', 3.5, '2023-05-03'),
(51, 'P051', 'B072', 3.5, '2023-05-03'),
(52, 'P052', 'B073', 3.5, '2023-05-03'),
(53, 'P053', 'B074', 3.5, '2023-05-03'),
(54, 'P054', 'B075', 3.5, '2023-05-03'),
(55, 'P055', 'B076', 3.5, '2023-05-03'),
(56, 'P056', 'B077', 3.5, '2023-05-03'),
(57, 'P057', 'B078', 3.5, '2023-05-03'),
(58, 'P058', 'B079', 3.5, '2023-05-03'),
(59, 'P059', 'B080', 3.5, '2023-05-03'),
(60, 'P060', 'B081', 3.5, '2023-05-03'),
(61, 'P061', 'B082', 3.5, '2023-05-03'),
(62, 'P062', 'B083', 3.5, '2023-05-04'),
(63, 'P063', 'B084', 7, '2023-05-15'),
(64, 'P064', 'B085', 3.5, '2023-05-15'),
(65, 'P065', 'B086', 7, '2023-05-15'),
(66, 'P066', 'B087', 3.5, '2023-05-15'),
(67, 'P067', 'B088', 3.5, '2023-05-15'),
(68, 'P068', 'B089', 4, '2023-05-15'),
(69, 'P069', 'B090', 3.5, '2023-05-15'),
(70, 'P070', 'B091', 3.5, '2023-05-23'),
(71, 'P071', 'B092', 7, '2023-05-31'),
(72, 'P072', 'B093', 3.5, '2023-05-31'),
(73, 'P073', 'B094', 3.5, '2023-05-31'),
(74, 'P074', 'B096', 3.5, '2023-05-31'),
(75, 'P075', NULL, 200, '2023-06-04'),
(76, 'P076', NULL, 200, '2023-06-07'),
(77, 'P077', 'B098', 4, '2023-06-07'),
(78, 'P078', 'B099', 3.5, '2023-06-17'),
(79, 'P079', NULL, 200, '2023-06-22'),
(80, 'P080', 'B0100', 4, '2023-06-26'),
(81, 'P081', 'B0101', 4, '2023-06-27'),
(82, 'P082', 'B0102', 4, '2023-06-27'),
(83, 'P083', 'B0103', 4, '2023-06-27'),
(84, 'P084', 'B0104', 4, '2023-06-27'),
(85, 'P085', 'B0105', 8, '2023-06-27'),
(86, 'P086', 'B0106', 4, '2023-06-27'),
(88, 'P088', 'B0108', 4, '2023-06-27'),
(89, 'P089', 'B0109', 4, '2023-06-27'),
(90, 'P090', NULL, 200, '2023-06-27'),
(91, 'P091', 'B0110', 3.5, '2023-06-27'),
(92, 'P092', 'B0111', 3.5, '2023-06-27');

-- --------------------------------------------------------

--
-- Table structure for table `staff`
--

CREATE TABLE `staff` (
  `Staff_id` varchar(10) NOT NULL,
  `Staff_name` varchar(50) NOT NULL,
  `Staff_ic` varchar(12) NOT NULL,
  `Staff_pass` varchar(10) NOT NULL,
  `Staff_phone` varchar(12) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `staff`
--

INSERT INTO `staff` (`Staff_id`, `Staff_name`, `Staff_ic`, `Staff_pass`, `Staff_phone`) VALUES
('Afzam03', 'Muhammad Afzam bin Hakim', '010703081003', 'Afzam03', '0162227688'),
('Collins18', 'Collins Henry', '990302100327', 'Collin1308', '0142382472'),
('Godzilla', 'Sim Wen Jing', '950703071002', 'WenJing03', '01733040347'),
('Kadijah', 'Kadijah', '021345070624', 'Kadijah13', '0123456895'),
('Rachell', 'rachell', '021345780923', 'Rachell12', '0132457890'),
('Syafiqah12', 'Syafiqah binti Fadzli', '021223100053', 'Syafiqah53', '0166680274');

-- --------------------------------------------------------

--
-- Table structure for table `staff_device`
--

CREATE TABLE `staff_device` (
  `NO` int(11) NOT NULL,
  `StaffDevice_id` varchar(10) NOT NULL,
  `Device_id` varchar(10) NOT NULL,
  `Staff_id` varchar(10) NOT NULL,
  `Staffdevice_date` date NOT NULL,
  `Remarks` varchar(30) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `staff_device`
--

INSERT INTO `staff_device` (`NO`, `StaffDevice_id`, `Device_id`, `Staff_id`, `Staffdevice_date`, `Remarks`) VALUES
(1, 'M01', 'PC001', 'Afzam03', '2023-05-23', 'Software setup'),
(12, 'M010', 'PC001', 'Collins18', '2023-06-27', 'HARDWARE SETUP'),
(2, 'M02', 'PC003', 'Syafiqah12', '2023-05-25', 'Network Configuration'),
(3, 'M03', 'PS002', 'Afzam03', '2023-05-25', 'Troubleshooting'),
(4, 'M04', 'PC002', 'Syafiqah12', '2023-05-24', 'HARDWARE REPAIR'),
(6, 'M05', 'PC001', 'Collins18', '2023-05-31', 'SECURITY SUPPORT'),
(7, 'M07', 'PC001', 'Collins18', '2023-06-05', 'SOFTWARE UPDATE'),
(8, 'M08', 'PC002', 'Collins18', '2023-06-27', 'Virus Scan'),
(9, 'M09', 'PC004', 'Collins18', '2023-06-27', 'Hardware Repair');

-- --------------------------------------------------------

--
-- Table structure for table `time_table`
--

CREATE TABLE `time_table` (
  `time_stamp` varchar(10) NOT NULL,
  `time` time DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `time_table`
--

INSERT INTO `time_table` (`time_stamp`, `time`) VALUES
('t1', '09:00:00'),
('t10', '18:00:00'),
('t11', '19:00:00'),
('t12', '20:00:00'),
('t13', '21:00:00'),
('t14', '22:00:00'),
('t2', '10:00:00'),
('t3', '11:00:00'),
('t4', '12:00:00'),
('t5', '13:00:00'),
('t6', '14:00:00'),
('t7', '15:00:00'),
('t8', '16:00:00'),
('t9', '17:00:00');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `admin`
--
ALTER TABLE `admin`
  ADD PRIMARY KEY (`Admin_id`);

--
-- Indexes for table `booking`
--
ALTER TABLE `booking`
  ADD PRIMARY KEY (`Booking_id`),
  ADD KEY `Booking_Device_FK` (`Device_id`),
  ADD KEY `Booking_Member_FK` (`Member_id`),
  ADD KEY `Booking_starttime_FK` (`start_time_stamp`) USING BTREE,
  ADD KEY `Booking_endtime_FK` (`end_time_stamp`) USING BTREE,
  ADD KEY `NO` (`NO`);

--
-- Indexes for table `device`
--
ALTER TABLE `device`
  ADD PRIMARY KEY (`Device_id`);

--
-- Indexes for table `invoice`
--
ALTER TABLE `invoice`
  ADD PRIMARY KEY (`Invoice_Number`),
  ADD KEY `Invoice_Payment_FK` (`Payment_id`) USING BTREE;

--
-- Indexes for table `member`
--
ALTER TABLE `member`
  ADD PRIMARY KEY (`Member_id`);

--
-- Indexes for table `payment`
--
ALTER TABLE `payment`
  ADD PRIMARY KEY (`Payment_id`),
  ADD KEY `Payment_Booking_FK` (`Booking_id`),
  ADD KEY `No` (`No`);

--
-- Indexes for table `staff`
--
ALTER TABLE `staff`
  ADD PRIMARY KEY (`Staff_id`);

--
-- Indexes for table `staff_device`
--
ALTER TABLE `staff_device`
  ADD PRIMARY KEY (`StaffDevice_id`),
  ADD KEY `Staff_device_Device_FK` (`Device_id`),
  ADD KEY `Staff_device_staff_FK` (`Staff_id`),
  ADD KEY `NO` (`NO`);

--
-- Indexes for table `time_table`
--
ALTER TABLE `time_table`
  ADD PRIMARY KEY (`time_stamp`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `booking`
--
ALTER TABLE `booking`
  MODIFY `NO` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=112;

--
-- AUTO_INCREMENT for table `invoice`
--
ALTER TABLE `invoice`
  MODIFY `Invoice_Number` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=68;

--
-- AUTO_INCREMENT for table `payment`
--
ALTER TABLE `payment`
  MODIFY `No` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=93;

--
-- AUTO_INCREMENT for table `staff_device`
--
ALTER TABLE `staff_device`
  MODIFY `NO` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=13;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `booking`
--
ALTER TABLE `booking`
  ADD CONSTRAINT `Booking_Device_FK` FOREIGN KEY (`Device_id`) REFERENCES `device` (`Device_id`),
  ADD CONSTRAINT `Booking_Member_FK` FOREIGN KEY (`Member_id`) REFERENCES `member` (`Member_id`),
  ADD CONSTRAINT `Booking_damn_FK` FOREIGN KEY (`end_time_stamp`) REFERENCES `time_table` (`time_stamp`),
  ADD CONSTRAINT `Booking_rembo_FK` FOREIGN KEY (`start_time_stamp`) REFERENCES `time_table` (`time_stamp`);

--
-- Constraints for table `payment`
--
ALTER TABLE `payment`
  ADD CONSTRAINT `Payment_Booking_FK` FOREIGN KEY (`Booking_id`) REFERENCES `booking` (`Booking_id`);

--
-- Constraints for table `staff_device`
--
ALTER TABLE `staff_device`
  ADD CONSTRAINT `Staff_device_Device_FK` FOREIGN KEY (`Device_id`) REFERENCES `device` (`Device_id`),
  ADD CONSTRAINT `Staff_device_staff_FK` FOREIGN KEY (`Staff_id`) REFERENCES `staff` (`Staff_id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
