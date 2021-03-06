USE [master]
GO
/****** Object:  Database [BanHang]    Script Date: 28-Dec-19 6:15:07 PM ******/
CREATE DATABASE [BanHang]
 CONTAINMENT = NONE
 ON  PRIMARY 
( NAME = N'BanHang', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL15.MSSQLSERVER\MSSQL\DATA\BanHang.mdf' , SIZE = 8192KB , MAXSIZE = UNLIMITED, FILEGROWTH = 65536KB )
 LOG ON 
( NAME = N'BanHang_log', FILENAME = N'C:\Program Files\Microsoft SQL Server\MSSQL15.MSSQLSERVER\MSSQL\DATA\BanHang_log.ldf' , SIZE = 8192KB , MAXSIZE = 2048GB , FILEGROWTH = 65536KB )
 WITH CATALOG_COLLATION = DATABASE_DEFAULT
GO
ALTER DATABASE [BanHang] SET COMPATIBILITY_LEVEL = 150
GO
IF (1 = FULLTEXTSERVICEPROPERTY('IsFullTextInstalled'))
begin
EXEC [BanHang].[dbo].[sp_fulltext_database] @action = 'enable'
end
GO
ALTER DATABASE [BanHang] SET ANSI_NULL_DEFAULT OFF 
GO
ALTER DATABASE [BanHang] SET ANSI_NULLS OFF 
GO
ALTER DATABASE [BanHang] SET ANSI_PADDING OFF 
GO
ALTER DATABASE [BanHang] SET ANSI_WARNINGS OFF 
GO
ALTER DATABASE [BanHang] SET ARITHABORT OFF 
GO
ALTER DATABASE [BanHang] SET AUTO_CLOSE OFF 
GO
ALTER DATABASE [BanHang] SET AUTO_SHRINK OFF 
GO
ALTER DATABASE [BanHang] SET AUTO_UPDATE_STATISTICS ON 
GO
ALTER DATABASE [BanHang] SET CURSOR_CLOSE_ON_COMMIT OFF 
GO
ALTER DATABASE [BanHang] SET CURSOR_DEFAULT  GLOBAL 
GO
ALTER DATABASE [BanHang] SET CONCAT_NULL_YIELDS_NULL OFF 
GO
ALTER DATABASE [BanHang] SET NUMERIC_ROUNDABORT OFF 
GO
ALTER DATABASE [BanHang] SET QUOTED_IDENTIFIER OFF 
GO
ALTER DATABASE [BanHang] SET RECURSIVE_TRIGGERS OFF 
GO
ALTER DATABASE [BanHang] SET  DISABLE_BROKER 
GO
ALTER DATABASE [BanHang] SET AUTO_UPDATE_STATISTICS_ASYNC OFF 
GO
ALTER DATABASE [BanHang] SET DATE_CORRELATION_OPTIMIZATION OFF 
GO
ALTER DATABASE [BanHang] SET TRUSTWORTHY OFF 
GO
ALTER DATABASE [BanHang] SET ALLOW_SNAPSHOT_ISOLATION OFF 
GO
ALTER DATABASE [BanHang] SET PARAMETERIZATION SIMPLE 
GO
ALTER DATABASE [BanHang] SET READ_COMMITTED_SNAPSHOT OFF 
GO
ALTER DATABASE [BanHang] SET HONOR_BROKER_PRIORITY OFF 
GO
ALTER DATABASE [BanHang] SET RECOVERY FULL 
GO
ALTER DATABASE [BanHang] SET  MULTI_USER 
GO
ALTER DATABASE [BanHang] SET PAGE_VERIFY CHECKSUM  
GO
ALTER DATABASE [BanHang] SET DB_CHAINING OFF 
GO
ALTER DATABASE [BanHang] SET FILESTREAM( NON_TRANSACTED_ACCESS = OFF ) 
GO
ALTER DATABASE [BanHang] SET TARGET_RECOVERY_TIME = 60 SECONDS 
GO
ALTER DATABASE [BanHang] SET DELAYED_DURABILITY = DISABLED 
GO
EXEC sys.sp_db_vardecimal_storage_format N'BanHang', N'ON'
GO
ALTER DATABASE [BanHang] SET QUERY_STORE = OFF
GO
USE [BanHang]
GO
/****** Object:  Table [dbo].[Bill]    Script Date: 28-Dec-19 6:15:08 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Bill](
	[ID] [char](10) NOT NULL,
	[IDPro] [char](10) NOT NULL,
	[IDCus] [char](10) NOT NULL,
 CONSTRAINT [PK_Bill] PRIMARY KEY CLUSTERED 
(
	[ID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[BILLinfo]    Script Date: 28-Dec-19 6:15:08 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[BILLinfo](
	[ID] [char](10) NOT NULL,
	[DateBuy] [char](20) NULL,
	[GiaTien] [char](10) NULL,
 CONSTRAINT [PK_BILLinfo] PRIMARY KEY CLUSTERED 
(
	[ID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Customer]    Script Date: 28-Dec-19 6:15:08 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Customer](
	[ID] [char](10) NOT NULL,
	[Name] [char](30) NULL,
	[Email] [char](30) NULL,
	[Phone] [nchar](10) NULL,
 CONSTRAINT [PK_Customer] PRIMARY KEY CLUSTERED 
(
	[ID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
/****** Object:  Table [dbo].[Product]    Script Date: 28-Dec-19 6:15:08 PM ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Product](
	[ID] [char](10) NOT NULL,
	[Name] [char](30) NULL,
	[Price] [int] NULL,
 CONSTRAINT [PK_Product] PRIMARY KEY CLUSTERED 
(
	[ID] ASC
)WITH (PAD_INDEX = OFF, STATISTICS_NORECOMPUTE = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS = ON, ALLOW_PAGE_LOCKS = ON, OPTIMIZE_FOR_SEQUENTIAL_KEY = OFF) ON [PRIMARY]
) ON [PRIMARY]
GO
INSERT [dbo].[Bill] ([ID], [IDPro], [IDCus]) VALUES (N'BI001     ', N'PR001     ', N'KH001     ')
INSERT [dbo].[Bill] ([ID], [IDPro], [IDCus]) VALUES (N'BI002     ', N'PR001     ', N'KH002     ')
INSERT [dbo].[Bill] ([ID], [IDPro], [IDCus]) VALUES (N'BI003     ', N'PR003     ', N'KH001     ')
INSERT [dbo].[Bill] ([ID], [IDPro], [IDCus]) VALUES (N'BI004     ', N'PR002     ', N'KH001     ')
INSERT [dbo].[Bill] ([ID], [IDPro], [IDCus]) VALUES (N'BI005     ', N'PR003     ', N'KH002     ')
INSERT [dbo].[Bill] ([ID], [IDPro], [IDCus]) VALUES (N'BI006     ', N'PR004     ', N'KH003     ')
INSERT [dbo].[Bill] ([ID], [IDPro], [IDCus]) VALUES (N'BI007     ', N'PR003     ', N'KH003     ')
INSERT [dbo].[Bill] ([ID], [IDPro], [IDCus]) VALUES (N'BI008     ', N'PR001     ', N'KH004     ')
INSERT [dbo].[Bill] ([ID], [IDPro], [IDCus]) VALUES (N'BI009     ', N'PR001     ', N'KH003     ')
INSERT [dbo].[Bill] ([ID], [IDPro], [IDCus]) VALUES (N'BI010     ', N'PR008     ', N'KH002     ')
INSERT [dbo].[Bill] ([ID], [IDPro], [IDCus]) VALUES (N'BI011     ', N'PR003     ', N'KH001     ')
INSERT [dbo].[BILLinfo] ([ID], [DateBuy], [GiaTien]) VALUES (N'BI001     ', N'2000-01-01          ', N'123000000 ')
INSERT [dbo].[BILLinfo] ([ID], [DateBuy], [GiaTien]) VALUES (N'BI002     ', N'2000-01-02          ', N'23000000  ')
INSERT [dbo].[BILLinfo] ([ID], [DateBuy], [GiaTien]) VALUES (N'BI003     ', N'2000-01-03          ', N'12000000  ')
INSERT [dbo].[BILLinfo] ([ID], [DateBuy], [GiaTien]) VALUES (N'BI004     ', N'2000-11-01          ', N'10500000  ')
INSERT [dbo].[BILLinfo] ([ID], [DateBuy], [GiaTien]) VALUES (N'BI005     ', N'2001-01-11          ', N'12300000  ')
INSERT [dbo].[BILLinfo] ([ID], [DateBuy], [GiaTien]) VALUES (N'BI006     ', N'2001-02-21          ', N'123040000 ')
INSERT [dbo].[BILLinfo] ([ID], [DateBuy], [GiaTien]) VALUES (N'BI007     ', N'2001-02-22          ', N'103000600 ')
INSERT [dbo].[BILLinfo] ([ID], [DateBuy], [GiaTien]) VALUES (N'BI008     ', N'2001-03-11          ', N'23005000  ')
INSERT [dbo].[BILLinfo] ([ID], [DateBuy], [GiaTien]) VALUES (N'BI009     ', N'2001-03-12          ', N'12307000  ')
INSERT [dbo].[BILLinfo] ([ID], [DateBuy], [GiaTien]) VALUES (N'BI010     ', N'2000-02-12          ', N'12900000  ')
INSERT [dbo].[BILLinfo] ([ID], [DateBuy], [GiaTien]) VALUES (N'BI011     ', N'2000-03-05          ', N'126500000 ')
INSERT [dbo].[Customer] ([ID], [Name], [Email], [Phone]) VALUES (N'KH001     ', N'Phan Van A           ', N'a123@gmail.com           ', N'12344444')
INSERT [dbo].[Customer] ([ID], [Name], [Email], [Phone]) VALUES (N'KH002     ', N'Nguyen Van B         ', N'b@gmail.com              ', N'12312314')
INSERT [dbo].[Customer] ([ID], [Name], [Email], [Phone]) VALUES (N'KH003     ', N'Ho Nguyen Vu         ', N'vu@gmail.com             ', N'0123456789')
INSERT [dbo].[Customer] ([ID], [Name], [Email], [Phone]) VALUES (N'KH004     ', N'Vuuu                 ', N'vuu@gmail.com            ', N'0948496162')
INSERT [dbo].[Customer] ([ID], [Name], [Email], [Phone]) VALUES (N'KH005     ', N'Nguyenn              ', N'123@gmail.com            ', N'12344')
INSERT [dbo].[Customer] ([ID], [Name], [Email], [Phone]) VALUES (N'KH006     ', N'Nguyennn             ', N'nguen@gmail.com          ', N'0123321123')
INSERT [dbo].[Product] ([ID], [Name], [Price]) VALUES (N'PR001     ', N'Dell 1                        ', 123000900)
INSERT [dbo].[Product] ([ID], [Name], [Price]) VALUES (N'PR002     ', N'Dell 2                        ', 99123000)
INSERT [dbo].[Product] ([ID], [Name], [Price]) VALUES (N'PR003     ', N'Dell 3                        ', 34000500)
INSERT [dbo].[Product] ([ID], [Name], [Price]) VALUES (N'PR004     ', N'Asus 1                        ', 45600000)
INSERT [dbo].[Product] ([ID], [Name], [Price]) VALUES (N'PR005     ', N'Dell 3                        ', 23500000)
INSERT [dbo].[Product] ([ID], [Name], [Price]) VALUES (N'PR008     ', N'Asus no hope 01               ', 99123000)
INSERT [dbo].[Product] ([ID], [Name], [Price]) VALUES (N'PR009     ', N'Asus Prime 1                  ', 12900000)
ALTER TABLE [dbo].[Bill]  WITH CHECK ADD  CONSTRAINT [FK_Bill_Customer] FOREIGN KEY([IDCus])
REFERENCES [dbo].[Customer] ([ID])
GO
ALTER TABLE [dbo].[Bill] CHECK CONSTRAINT [FK_Bill_Customer]
GO
ALTER TABLE [dbo].[Bill]  WITH CHECK ADD  CONSTRAINT [FK_Bill_Product] FOREIGN KEY([IDPro])
REFERENCES [dbo].[Product] ([ID])
GO
ALTER TABLE [dbo].[Bill] CHECK CONSTRAINT [FK_Bill_Product]
GO
ALTER TABLE [dbo].[BILLinfo]  WITH CHECK ADD  CONSTRAINT [FK_BILLinfo_Bill] FOREIGN KEY([ID])
REFERENCES [dbo].[Bill] ([ID])
GO
ALTER TABLE [dbo].[BILLinfo] CHECK CONSTRAINT [FK_BILLinfo_Bill]
GO
USE [master]
GO
ALTER DATABASE [BanHang] SET  READ_WRITE 
GO
