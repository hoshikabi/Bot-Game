
const axios = require('axios');

const OWNER = 'Dolphin-kun';
const REPO = 'discord_bot_template';

// 通知先チャンネルID
const CHANNEL_ID = '1567461833437216789';

let latestCommit = null;

async function checkGitHub(client) {
    try {
        const token = process.env.GITHUB_TOKEN;

        if (!token) {
            console.error('GITHUB_TOKENが設定されていません');
            return;
        }

        const response = await axios.get(
            `https://api.github.com/repos/${OWNER}/${REPO}/commits`,
            {
                headers: {
                    Accept: 'application/vnd.github+json',
                    Authorization: `Bearer ${token}`
                },
                params: {
                    per_page: 1
                }
            }
        );

        const commit = response.data[0];

        if (!commit) return;

        // 初回は最新コミットを記録するだけ
        if (latestCommit === null) {
            latestCommit = commit.sha;
            console.log('GitHub監視を開始しました');
            return;
        }

        // 新しいコミットがあった場合
        if (latestCommit !== commit.sha) {
            latestCommit = commit.sha;

            const channel = await client.channels.fetch(CHANNEL_ID);

            if (!channel || !channel.isTextBased()) return;

            await channel.send({
                content:
                    `📢 **GitHubが更新されました！**\n` +
                    `📁 リポジトリ: ${OWNER}/${REPO}\n` +
                    `👤 更新者: ${commit.commit.author.name}\n` +
                    `📝 内容: ${commit.commit.message}\n` +
                    `🔗 URL: ${commit.html_url}`
            });

            console.log('GitHubの更新を通知しました');
        }

    } catch (error) {
        console.error('GitHub監視エラー:', error.message);
        console.error('HTTPステータス:', error.response?.status);
        console.error('GitHubの応答:', error.response?.data);
        console.error('API残り回数:', error.response?.headers?.['x-ratelimit-remaining']);
    }
}

function startGitHubMonitor(client) {
    checkGitHub(client);

    setInterval(() => {
        checkGitHub(client);
    }, 60 * 1000);
}

module.exports = { startGitHubMonitor };
